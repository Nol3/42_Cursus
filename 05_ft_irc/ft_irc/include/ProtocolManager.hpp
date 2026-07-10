#ifndef PROTOCOL_MANAGER_HPP
# define PROTOCOL_MANAGER_HPP

# include <string>
# include <map>
# include <vector>
# include <iostream>

// Declaración adelantada (Forward declaration) para evitar incluir irce.hpp aquí
class irce;

/**
 * @brief Gestiona la lógica del protocolo IRC.
 *
 * @details Esta clase es responsable de parsear los mensajes raw que llegan
 * del servidor (`irce`), interpretar los comandos (NICK, USER, PASS, PRIVMSG, etc.),
 * gestionar el estado de registro de los clientes y
 * utilizar la API de `irce` para enviar respuestas.
 */
class ProtocolManager {
private:
    // Referencia al servidor principal para poder llamarlo (enviar respuestas, desconectar, etc.)
    irce* server;

    /**
     * @brief Estructura que representa un mensaje IRC parseado.
     * @details Separa el mensaje raw en sus componentes principales:
     * prefijo (opcional), comando, parámetros y trailing (opcional).
     */
    struct IRCMsg {
        std::string prefix;
        std::string command;
        std::vector<std::string> params;
        std::string trailing;
    };

    // Puntero a una función miembro de ProtocolManager que maneja un comando.
    typedef void (ProtocolManager::*CommandHandler)(int, const IRCMsg&);

    // Mapa que asocia un string de comando (ej. "NICK") a su función manejadora.
    std::map<std::string, CommandHandler> commandHandlers;

    // --- Estado de registro de clientes ---
    // Almacena el NICK de cada cliente (por fd)
    std::map<int, std::string> clientNick;
    // Almacena si un cliente ha enviado el comando USER (por fd)
    std::map<int, bool> clientHasUser;

    /**
     * @brief Intenta completar el registro de un cliente.
     *
     * @details Comprueba si el cliente ya ha enviado NICK, USER y
     * la PASS correcta (si es necesaria). Si todo está completo,
     * envía el mensaje de bienvenida (RPL_WELCOME 001) y marca
     * al cliente como registrado en el servidor.
     *
     * @param clientFd El file descriptor del cliente.
     */
    void tryCompleteRegistration(int clientFd);

    // --- Métodos de parseo ---

    /**
     * @brief Parsea un mensaje raw de IRC a una estructura IRCMsg.
     *
     * @details Descompone la línea de texto según la especificación IRC
     * (RFC 2812), separando prefijo, comando, parámetros y trailing.
     *
     * @param rawMessage El mensaje raw (sin \r\n).
     * @return IRCMsg La estructura con el mensaje parseado.
     */
    IRCMsg parseMessage(const std::string& rawMessage);

    /**
     * @brief Comprueba si un nickname ya está en uso.
     * @param nick El nickname a comprobar.
     * @return bool `true` si está en uso, `false` si no.
     */
    bool isNicknameInUse(const std::string& nick) const;

    // --- Manejadores de comandos (Command handlers) ---

    /** @brief Maneja el comando NICK. */
    void NICKcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando USER. */
    void USERcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando PASS. */
    void PASScmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando JOIN. */
    void JOINcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando PRIVMSG (mensajes a canal o usuario). */
    void PRIVMSGcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando NOTICE (similar a PRIVMSG pero sin respuestas de error). */
    void NOTICEcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando KICK (expulsar usuario del canal, solo operadores). */
    void KICKcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando INVITE (invitar usuario a canal, solo operadores). */
    void INVITEcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando TOPIC (ver/cambiar tema del canal). */
    void TOPICcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando MODE (cambiar modos del canal). */
    void MODEcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando PING (para mantener la conexión). */
    void PINGcmd(int clientFd, const IRCMsg& message);
    /** @brief Maneja el comando QUIT. */
    void QUITcmd(int clientFd, const IRCMsg& message);

    // ---- Helpers/Utils ----

    /**
     * @brief Comprueba si un nickname ya está en uso.
     * @param nick El nickname a comprobar.
     * @return bool `true` si está en uso, `false` si no.
     */
    bool isNickInUse(const std::string& nick);

    /** @brief Actualiza el nickname de un cliente. */
    void updClientNick(int clientFd, const std::string& newNick);
    /** @brief Añade un cliente a un canal (llama a `server`). */
    void addClientToChannel(int clientFd, const std::string& channelName);

    /** @brief Comprueba si un nombre corresponde a un canal (empieza por '#'). */
    bool isChannel(const std::string& name);

    /** @brief Envía un mensaje privado a un usuario específico (por nickname). */
    void sendMessageToUser(const std::string& target, int clientFd, const std::string& message);

    /** @brief Desconecta a un cliente (llama a `server`). */
    void disconnectClient(int clientFd);

    // --- Métodos de ayuda para respuestas ---

    /**
     * @brief Envía una respuesta raw al cliente (llama a `server->queueSend`).
     * @param clientFd FD del cliente.
     * @param response Mensaje completo a enviar (sin \r\n).
     */
    void sendResponse(int clientFd, const std::string& response);

    /**
     * @brief Construye y envía una respuesta numérica estándar de IRC (RPL).
     * @param clientFd FD del cliente.
     * @param code El código numérico (ej. 464, 001).
     * @param nickname El nickname al que se dirige la respuesta (o "*" si no aplica).
     * @param message El texto de la respuesta.
     */
    void sendNumericResponse(int clientFd, int code, const std::string& nickname, const std::string& message);

public:
    /**
     * @brief Constructor del ProtocolManager.
     * @details Inicializa la referencia al servidor y rellena el mapa de comandos
     * (`commandHandlers`) asociando cada string de comando a su función.
     * @param serverRef Puntero a la instancia principal del servidor `irce`.
     */
    ProtocolManager(irce* serverRef);

    /** @brief Destructor. */
    ~ProtocolManager();

    /**
     * @brief Punto de entrada principal para procesar un comando.
     *
     * @details Esta función es llamada por `irce::handleClientMessage`.
     * Parsea el mensaje, aplica la lógica de registro (PASS/NICK/USER)
     * y, si el cliente está registrado, despacha el comando a su
     * manejador correspondiente (ej. `PRIVMSGcmd`).
     *
     * @param clientFd El FD del cliente que envía el comando.
     * @param input El mensaje raw (línea completa sin \r\n).
     */
    void processCommand(int clientFd, const std::string& input);

    /**
     * @brief Notificación llamada por `irce` cuando un cliente se desconecta.
     * @details Se usa para limpiar el estado interno (nick, user) de
     * ese cliente en el ProtocolManager.
     * @param clientFd El FD del cliente que se ha desconectado.
     */
    void onClientDisconnected(int clientFd);
};

#endif