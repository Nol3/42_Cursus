#ifndef IRCE_HPP
 # define IRCE_HPP

# include <iostream>
# include <vector>
# include <map>
# include <string>
# include <deque>
# include <set>
# include <cstring>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include <fcntl.h>
# include <algorithm>
# include <errno.h>

#include "ProtocolManager.hpp"

/**
 * @brief Clase principal del servidor IRC.
 *
 * @details Gestiona las conexiones de red (sockets, poll), el estado de los
 * clientes, los buffers de E/S, los canales y delega el procesamiento de
 * comandos IRC al ProtocolManager.
 */
class irce {
private:
    int server_socket;
    std::vector<pollfd> poll_fds;
    ProtocolManager *protocol_manager;
    std::string server_password;

    /**
     * @brief Almacena el estado completo de un cliente conectado.
     * @details Incluye el file descriptor, buffers de lectura/escritura,
     * estado de autenticación (PASS) y registro (NICK/USER),
     * y los datos del usuario.
     */
    struct ClientState {
        int fd;
        std::string readBuffer;
        std::deque<std::string> writeQueue;
        bool passOk;
        bool registered;
        std::string nickname;
        std::string realname;
        std::string host;
        std::string port;
        bool pendingDisconnect;
    };

    std::map<int, ClientState> clients;
    std::map<std::string, std::set<int> > channels; // canal -> fds
    std::map<std::string, std::set<int> > channelOperators; // canal → fds de operadores
    std::map<std::string, std::string> channelTopics; // canal → tema del canal

    // Modos de canal
    std::map<std::string, bool> channelInviteOnly; // canal → +i (invite-only)
    std::map<std::string, bool> channelTopicProtected; // canal → +t (topic protected)
    std::map<std::string, std::string> channelKeys; // canal → contraseña (+k)
    std::map<std::string, int> channelLimits; // canal → límite de usuarios (+l)
    std::map<std::string, std::set<int> > channelInvites; // canal → fds de usuarios invitados

    // Parte 1: Manejo de Conexiones

    /**
     * @brief Inicializa el socket principal del servidor.
     *
     * @details Crea, configura (SO_REUSEADDR, O_NONBLOCK), enlaza (bind) y
     * pone en modo escucha (listen) el socket del servidor.
     * Finalmente, lo añade al vector de poll_fds.
     *
     * @param port El puerto en el que el servidor debe escuchar.
     * @return bool `true` si la inicialización fue exitosa, `false` si hubo algún error.
     */
    bool initServer(int port);

    /**
     * @brief Configura un file descriptor (socket) como no bloqueante.
     *
     * @param fd El file descriptor a modificar.
     * @return bool `true` si se pudo establecer el modo no bloqueante, `false` en caso de error.
     */
    bool setNonBlocking(int fd);

    /**
     * @brief Acepta y gestiona nuevas conexiones de clientes entrantes.
     *
     * @details Acepta conexiones en bucle (hasta EWOULDBLOCK), configura el
     * nuevo socket de cliente como no bloqueante, crea su ClientState y lo
     * registra en poll_fds y en el mapa de clients.
     */
    void handleNewConnection();

    /**
     * @brief Busca el índice de un file descriptor en poll_fds.
     *
     * @param fd El file descriptor a buscar.
     * @return size_t El índice en poll_fds, o -1 si no se encontró.
     */
    size_t findPollIndex(int fd);

    /**
     * @brief Desconecta a un cliente del servidor y limpia sus recursos.
     *
     * @details Cierra el socket, elimina al cliente del mapa `clients`, del
     * vector `poll_fds` y de todos los canales en los que estaba.
     * Notifica al ProtocolManager sobre la desconexión.
     *
     * @param fd El file descriptor del cliente a desconectar.
     * @param poll_index El índice del cliente en el vector `poll_fds` (para una eliminación eficiente).
     */
    void disconnectClient(int fd, size_t poll_index);

    /**
     * @brief Maneja un error de socket detectado por poll (POLLERR, POLLHUP, POLLNVAL).
     *
     * @param poll_index El índice en `poll_fds` del socket que reportó el error.
     */
    void handleSocketError(size_t poll_index);

    /**
     * @brief Activa o desactiva la monitorización del evento de escritura (POLLOUT) para un cliente.
     *
     * @param pollIndex El índice en `poll_fds` del cliente.
     * @param enable `true` para activar POLLOUT (monitorizar escritura), `false` para desactivarlo.
     */
    void enableWriteEvent(size_t pollIndex, bool enable);

    /**
     * @brief Envía datos pendientes a un cliente cuando el socket está listo para escribir (POLLOUT).
     *
     * @details Procesa la `writeQueue` del cliente. Envía tantos datos como
     * sea posible sin bloquear. Maneja envíos parciales. Si la cola se
     * vacía, desactiva POLLOUT para ese cliente.
     *
     * @param client_fd El file descriptor del cliente.
     * @param pollIndex El índice del cliente en `poll_fds`.
     */
    void handleWritableClient(int client_fd, size_t pollIndex);

    // Parte de chemita (protocolos y parseo)
    void handleClientMessage(int client_fd);

    /**
     * @brief (Interno) Añade un cliente a un canal.
     * @param client_fd FD del cliente.
     * @param channel_name Nombre del canal.
     */
    void joinChannel(int client_fd, const std::string& channel_name);

public:
    /**
     * @brief Constructor del servidor IRC.
     * @param pwd La contraseña requerida para conectarse al servidor (vacía si no hay contraseña).
     */
    irce(const std::string& pwd);

    /**
     * @brief Destructor. Libera recursos.
     * @details Elimina el ProtocolManager y cierra todos los sockets abiertos.
     */
    ~irce();

    /**
     * @brief Inicia y ejecuta el bucle principal del servidor.
     *
     * @details Llama a `initServer` y luego entra en un bucle infinito que
     * espera eventos usando `poll()`. Despacha los eventos (nueva conexión,
     * error, lectura, escritura) a sus respectivos manejadores (`handle...`).
     * Esta función es bloqueante y no retorna a menos que haya un error fatal en poll.
     *
     * @param port El puerto en el que se iniciará el servidor.
     */
    void run(int port);

    /**
     * @brief Encola un mensaje para ser enviado a un cliente (API para ProtocolManager).
     *
     * @details Añade la línea de mensaje (añadiendo `\r\n` automáticamente)
     * a la `writeQueue` del cliente. Activa el evento `POLLOUT` para
     * que el bucle principal se encargue de enviarlo.
     *
     * @param client_fd El fd del cliente destinatario.
     * @param line El mensaje a enviar (sin `\r\n`).
     */
    void queueSend(int client_fd, const std::string& line);

    /**
     * @brief Marca si un cliente ha proporcionado la contraseña correcta (API para ProtocolManager).
     * @param client_fd FD del cliente.
     * @param ok `true` si la contraseña es correcta, `false` en caso contrario.
     */
    void markPassOk(int client_fd, bool ok);

    /**
     * @brief Marca si un cliente ha completado el registro (API para ProtocolManager).
     * @param client_fd FD del cliente.
     * @param ok `true` si el registro está completo, `false` en caso contrario.
     */
    void markRegistered(int client_fd, bool ok);

    // API pública mínima para autenticación/gestión

    /**
     * @brief Comprueba si el servidor tiene una contraseña configurada.
     * @return bool `true` si no hay contraseña, `false` si la hay.
     */
    bool isPasswordEmpty() const { return server_password.empty(); }

    /**
     * @brief Valida una contraseña contra la del servidor.
     * @param pass La contraseña a comprobar.
     * @return bool `true` si la contraseña coincide, `false` si no.
     */
    bool isPasswordValid(const std::string &pass) const { return pass == server_password; }

    /**
     * @brief Comprueba si un cliente ha superado la validación de contraseña.
     * @param client_fd FD del cliente.
     * @return bool `true` si el cliente ha enviado la contraseña correcta.
     */
    bool isPassOk(int client_fd) const { std::map<int, ClientState>::const_iterator it = clients.find(client_fd); return it != clients.end() && it->second.passOk; }

    /**
     * @brief Comprueba si un cliente ha completado el registro.
     * @param client_fd FD del cliente.
     * @return bool `true` si el cliente está registrado (NICK/USER).
     */
    bool isRegistered(int client_fd) const { std::map<int, ClientState>::const_iterator it = clients.find(client_fd); return it != clients.end() && it->second.registered; }

    /**
     * @brief Verifica si un cliente es operador de un canal
     * @param client_fd FD del cliente
     * @param channel_name Nombre del canal
     * @return true si es operador, false si no
     */
    bool isChannelOperator(int client_fd, const std::string& channel_name) const;

    /**
     * @brief Obtiene el tema de un canal
     * @param channel_name Nombre del canal
     * @return El tema del canal o string vacío si no tiene tema
     */
    std::string getChannelTopic(const std::string& channel_name) const;

    /**
     * @brief Establece el tema de un canal
     * @param channel_name Nombre del canal
     * @param topic Nuevo tema
     */
    void setChannelTopic(const std::string& channel_name, const std::string& topic);

    /**
     * @brief Rellena la información de un usuario
     * 
     * @param client_fd 
     * @param userdata 
     */
    int setUser(int client_fd, std::string nick, std::string user, std::string host, std::string port);

    /**
     * @brief Obtiene el conjunto de clientes de un canal
     * @param channel_name Nombre del canal
     * @return Set de FDs de clientes en el canal
     */
    std::set<int> getChannelClients(const std::string& channel_name) const;

    /**
     * @brief Obtiene todos los nicknames actuales
     * @return Mapa de FD → nickname
     */
    std::map<int, std::string> getAllNicknames() const;

    /**
     * @brief Obtiene el nickname de un cliente
     * @param client_fd FD del cliente
     * @return El nickname del cliente o string vacío
     */
    std::string getClientNick(int client_fd) const;

    /**
     * @brief Establece el nickname de un cliente
     * @param client_fd FD del cliente
     * @param nickname Nuevo nickname
     */
    void setClientNick(int client_fd, const std::string& nickname);

    // ==================== GESTIÓN DE MODOS DE CANAL ====================

    /**
     * @brief Verifica si un canal tiene modo +i (invite-only)
     */
    bool isChannelInviteOnly(const std::string& channel_name) const;

    /**
     * @brief Establece modo +i/-i
     */
    void setChannelInviteOnly(const std::string& channel_name, bool value);

    /**
     * @brief Verifica si un canal tiene modo +t (topic protected)
     */
    bool isChannelTopicProtected(const std::string& channel_name) const;

    /**
     * @brief Establece modo +t/-t
     */
    void setChannelTopicProtected(const std::string& channel_name, bool value);

    /**
     * @brief Obtiene la contraseña de un canal (+k)
     */
    std::string getChannelKey(const std::string& channel_name) const;

    /**
     * @brief Establece contraseña +k (o vacío para -k)
     */
    void setChannelKey(const std::string& channel_name, const std::string& key);

    /**
     * @brief Obtiene el límite de usuarios de un canal (+l)
     */
    int getChannelLimit(const std::string& channel_name) const;

    /**
     * @brief Establece límite +l (o -1 para -l)
     */
    void setChannelLimit(const std::string& channel_name, int limit);

    /**
     * @brief Añade operador a un canal (+o)
     */
    void addChannelOperator(const std::string& channel_name, int client_fd);

    /**
     * @brief Quita operador de un canal (-o)
     */
    void removeChannelOperator(const std::string& channel_name, int client_fd);

    /**
     * @brief Desconecta a un cliente (API pública).
     * @details Busca el índice `poll_fds` del cliente y llama a `disconnectClient`.
     * @param client_fd FD del cliente a desconectar.
     */
    void disconnectFd(int client_fd) { for (size_t i = 0; i < poll_fds.size(); ++i) { if (poll_fds[i].fd == client_fd) { disconnectClient(client_fd, i); break; } } }

    /**
     * @brief Marca un cliente para desconexión después de vaciar su cola de escritura
     * @param client_fd FD del cliente
     */
    void markForDisconnect(int client_fd);

    /**
     * @brief Añade un cliente a un canal (con validación de modos).
     * @param client_fd FD del cliente.
     * @param channel_name Nombre del canal.
     * @param key Contraseña del canal (opcional).
     * @return true si se unió exitosamente, false si fue rechazado.
     */
    bool addClientToChannel(int client_fd, const std::string& channel_name, const std::string& key = "");

    /**
     * @brief (API Pública) Envía un mensaje *raw* a un canal, excluyendo al remitente.
     * @param client_fd FD del remitente (para excluir).
     * @param channel_name Canal de destino.
     * @param rawLine La línea de mensaje *completa* (incluyendo prefijo, comando, etc.) a enviar.
     */
    void broadcastToChannel(int client_fd, const std::string& channel_name, const std::string& rawLine);

    /**
     * @brief Remueve un cliente de un canal
     * @param client_fd FD del cliente
     * @param channel_name Nombre del canal
     */
    void removeClientFromChannel(int client_fd, const std::string& channel_name);
    
    /**
     * @brief Añade un usuario a la lista de invitados de un canal
     * @param channel_name Nombre del canal
     * @param client_fd FD del usuario invitado
     */
    void addChannelInvite(const std::string& channel_name, int client_fd);
    
    /**
     * @brief Verifica si un usuario está invitado a un canal
     * @param channel_name Nombre del canal
     * @param client_fd FD del usuario
     * @return true si está invitado, false en caso contrario
     */
    bool isUserInvited(const std::string& channel_name, int client_fd);
    
    /**
     * @brief Remueve un usuario de la lista de invitados (cuando se une al canal)
     * @param channel_name Nombre del canal
     * @param client_fd FD del usuario
     */
    void removeChannelInvite(const std::string& channel_name, int client_fd);
};

#endif