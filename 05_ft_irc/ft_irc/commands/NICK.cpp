#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::NICKcmd(int clientFd, const IRCMsg &message)
{
    std::string oldNick = clientNick[clientFd];
    std::string newNick;
    if (!message.params.empty()) {
        newNick = message.params[0];
    } else if (!message.trailing.empty()) {
        newNick = message.trailing;
    }

    if (isNicknameInUse(newNick) && clientNick[clientFd] != newNick) {
        sendNumericResponse(clientFd, 433, newNick, "Nickname is already in use");
        return;
    }

    newNick.erase(std::remove(newNick.begin(), newNick.end(), '\r'), newNick.end());
    newNick.erase(std::remove(newNick.begin(), newNick.end(), '\n'), newNick.end());
    updClientNick(clientFd, newNick);

    tryCompleteRegistration(clientFd);
    if (oldNick.empty())
        sendNumericResponse(clientFd, 1, clientNick[clientFd],"Your nickname now is " + clientNick[clientFd]);
    else
        sendNumericResponse(clientFd, 1, clientNick[clientFd], oldNick + ", your new nickname is " + clientNick[clientFd]);
}