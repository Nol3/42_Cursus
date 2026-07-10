#include "../include/irce.hpp"

//==============================================================================//
//                              GETTERS&SETTERS                                 //
//==============================================================================//

std::map<int, std::string> irce::getAllNicknames() const {
    std::map<int, std::string> result;
    for (std::map<int, ClientState>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
        if (!it->second.nickname.empty()) {
            result[it->first] = it->second.nickname;
        }
    }
    return result;
}

std::string irce::getClientNick(int client_fd) const {
    std::map<int, ClientState>::const_iterator it = clients.find(client_fd);
    if (it == clients.end()) return "";
    return it->second.nickname;
}


void irce::setClientNick(int client_fd, const std::string& nickname) {
    std::map<int, ClientState>::iterator it = clients.find(client_fd);
    if (it != clients.end()) {
        it->second.nickname = nickname;
    }
}

int irce::setUser(int client_fd, std::string nick, std::string user, std::string host, std::string port)
{
    if (clients.find(client_fd) == clients.end()) return -1;
    
    std::map<int, ClientState>::iterator it = clients.begin();
    
    while (it != clients.end()) {
        if (it->first != client_fd && it->second.nickname == nick) {
            return 1;
        }
        it++;
    }
    it = clients.begin();
    while (it != clients.end()) {
        if (it->first != client_fd && it->second.realname == user) {
            return 2;
        }
        it++;
    }
    clients[client_fd].nickname = nick;
    clients[client_fd].realname = user;
    clients[client_fd].host = host;
    clients[client_fd].port = port;
    return 0;
}

//==============================================================================//
//                              CLIENT MARKING                                  //
//==============================================================================//

void irce::markPassOk(int client_fd, bool ok) {
    clients[client_fd].passOk = ok;
}

void irce::markRegistered(int client_fd, bool ok) {
    clients[client_fd].registered = ok;
}

void irce::markForDisconnect(int client_fd) {
    std::map<int, ClientState>::iterator it = clients.find(client_fd);
    if (it != clients.end()) {
        it->second.pendingDisconnect = true;
    }
}

