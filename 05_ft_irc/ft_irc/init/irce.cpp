#include "../include/irce.hpp"

irce::irce(const std::string& pwd) : server_socket(-1), server_password(pwd) 
{
    protocol_manager = new ProtocolManager(this);
}

irce::~irce() 
{
    delete protocol_manager;
    for (std::vector<pollfd>::iterator it = poll_fds.begin(); it != poll_fds.end(); ++it) {
        close(it->fd);
    }
}


bool irce::initServer(int port)
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        std::cerr << "Error creando socket" << std::endl;
        return false;
    }

    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error en setsockopt" << std::endl;
        return false;
    }
    
    if (!setNonBlocking(server_socket)) {
        std::cerr << "Error poniendo server_socket en no bloqueante" << std::endl;
        return false;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error enlazando socket" << std::endl;
        return false;
    }

    if (listen(server_socket, 10) < 0) {
        std::cerr << "Error en listen" << std::endl;
        return false;
    }

    pollfd server_pollfd;
    server_pollfd.fd = server_socket;
    server_pollfd.events = POLLIN;
    server_pollfd.revents = 0;
    poll_fds.push_back(server_pollfd);

    std::cout << "Servidor iniciado en puerto " << port << std::endl;
    return true;
}

void irce::handleClientMessage(int client_fd)
{
    char buf[1024];
    ssize_t n = recv(client_fd, buf, sizeof(buf), 0);

    if (n <= 0) {
        if (n == 0 || (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK)) {
            size_t index = findPollIndex(client_fd);
            if (index != (size_t)-1) {
                disconnectClient(client_fd, index);
            }
        }
        return;
    }

    ClientState &st = clients[client_fd];
    st.readBuffer.append(buf, buf + n);

    if (st.readBuffer.size() > 8192) 
    {
        size_t index = findPollIndex(client_fd);
        if (index != (size_t)-1) {
            disconnectClient(client_fd, index);
        }
        return;
    }

    size_t pos;
    while ((pos = st.readBuffer.find("\r\n")) != std::string::npos) {
        std::string raw = st.readBuffer.substr(0, pos);
        st.readBuffer.erase(0, pos + 2);
        protocol_manager->processCommand(client_fd, raw);
    }
}

void irce::run(int port)
{
    if (!initServer(port)) {
        std::cerr << "No se pudo iniciar el servidor" << std::endl;
        return;
    }

    std::cout << "Servidor IRC iniciado. Esperando conexiones..." << std::endl;
    while (true) {
        int ret = poll(poll_fds.data(), poll_fds.size(), -1);
        if (ret < 0) {
            std::cerr << "poll() error" << std::endl;
            break;
        }

        for (size_t i = 0; i < poll_fds.size(); ++i) {
            short re = poll_fds[i].revents;
            if (!re) continue;

            if (re & (POLLERR | POLLHUP | POLLNVAL)) {
                handleSocketError(i);
                --i;
                continue;
            }

            if ((re & POLLIN) && poll_fds[i].fd == server_socket) {
                handleNewConnection();
                continue;
            }

            if (re & POLLIN) {
                int cfd = poll_fds[i].fd;
                handleClientMessage(cfd);
                continue;
            }

            if (re & POLLOUT) {
                int cfd = poll_fds[i].fd;
                handleWritableClient(cfd, i);
                continue;
            }
        }
    }
}
