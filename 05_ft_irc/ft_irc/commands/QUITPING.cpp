#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::PINGcmd(int clientFd, const IRCMsg &message)
{
    std::string token = message.trailing;
    if (token.empty() && !message.params.empty()) token = message.params[0];
    server->queueSend(clientFd, "PONG :" + token);
}

void ProtocolManager::QUITcmd(int clientFd, const IRCMsg &message)
{
    std::string quitMsg = ":server QUIT :";
    if (!message.trailing.empty()) {
        quitMsg += message.trailing;
    } else {
        quitMsg += "Client quit";
    }

    server->queueSend(clientFd, quitMsg);
    server->markForDisconnect(clientFd);
}