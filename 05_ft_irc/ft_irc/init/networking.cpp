#include "../include/irce.hpp"

void irce::handleNewConnection()
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
    if (client_socket < 0) {
        return;
    }
    if (!setNonBlocking(client_socket)) {
        close(client_socket);
        return;
    }

    pollfd client_pollfd;
    client_pollfd.fd = client_socket;
    client_pollfd.events = POLLIN;
    client_pollfd.revents = 0;
    poll_fds.push_back(client_pollfd);

    ClientState st;
    st.fd = client_socket;
    st.passOk = (server_password.empty());
    st.registered = false;
    st.pendingDisconnect = false;
    clients[client_socket] = st;

    std::cout << "Nueva conexión en socket " << client_socket << std::endl;
}

void irce::disconnectClient(int fd, size_t poll_index)
{
    close(fd);
    clients.erase(fd);
    poll_fds.erase(poll_fds.begin() + poll_index);
    std::cout << "Desconectado fd " << fd << std::endl;
    if (protocol_manager) {
        protocol_manager->onClientDisconnected(fd);
    }
    for (std::map<std::string, std::set<int> >::iterator it = channels.begin(); it != channels.end(); ++it) {
        it->second.erase(fd);
    }
    for (std::map<std::string, std::set<int> >::iterator it = channelOperators.begin(); it != channelOperators.end(); ++it) {
        it->second.erase(fd);
    }
    for (std::map<std::string, std::set<int> >::iterator it = channelInvites.begin(); it != channelInvites.end(); ++it) {
        it->second.erase(fd);
    }
}

void irce::enableWriteEvent(size_t pollIndex, bool enable) {
    if (enable) poll_fds[pollIndex].events |= POLLOUT;
    else poll_fds[pollIndex].events &= ~POLLOUT;
}

bool irce::setNonBlocking(int fd) {
    return fcntl(fd, F_SETFL, O_NONBLOCK) != -1;
}

size_t irce::findPollIndex(int fd)
{
    for (size_t i = 0; i < poll_fds.size(); ++i) {
        if (poll_fds[i].fd == fd) return i;
    }
    return (size_t)-1;
}

void irce::handleWritableClient(int client_fd, size_t pollIndex) {
    ClientState &st = clients[client_fd];
    while (!st.writeQueue.empty()) {
        const std::string &msg = st.writeQueue.front();
        ssize_t sent = send(client_fd, msg.data(), msg.size(), 0);
        if (sent < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            disconnectClient(client_fd, pollIndex);
            return;
        }
        if (static_cast<size_t>(sent) < msg.size()) {
            st.writeQueue.front().erase(0, sent);
            break;
        }
        st.writeQueue.pop_front();
    }
    if (st.writeQueue.empty()) {
        enableWriteEvent(pollIndex, false);
        if (st.pendingDisconnect) {
            disconnectClient(client_fd, pollIndex);
            return;
        }
    }
}

void irce::queueSend(int client_fd, const std::string& line) 
{
    ClientState &st = clients[client_fd];
    st.writeQueue.push_back(line + "\r\n");
    for (size_t i = 0; i < poll_fds.size(); ++i) {
        if (poll_fds[i].fd == client_fd) {
            enableWriteEvent(i, true);
            break;
        }
    }
}

void irce::handleSocketError(size_t poll_index) {
    int fd = poll_fds[poll_index].fd;
    disconnectClient(fd, poll_index);
}
