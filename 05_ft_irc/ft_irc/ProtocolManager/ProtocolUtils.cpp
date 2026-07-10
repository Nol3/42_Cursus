#include "../include/ProtocolManager.hpp"
#include <algorithm>
#include "../include/irce.hpp"
#include <sstream>

bool ProtocolManager::isNickInUse(const std::string& nick)
{   
    for (std::map<int, std::string>::const_iterator it = clientNick.begin(); it != clientNick.end(); ++it)
    {
        if (it->second == nick)
            return true;
    }
    return false;
}

void ProtocolManager::updClientNick(int clientFd, const std::string& newNick)
{
    clientNick[clientFd] = newNick;
    server->setClientNick(clientFd, newNick); // Sincronizar con irce
}

void ProtocolManager::addClientToChannel(int clientFd, const std::string& channelName)
{
    server->addClientToChannel(clientFd, channelName);
}

bool ProtocolManager::isChannel(const std::string& name)
{
    return !name.empty() && (name[0] == '#' || name[0] == '&'); // (Añadido '&' por estándar IRC)
}

void ProtocolManager::sendMessageToUser(const std::string& target, int clientFd, const std::string& message)
{
    int targetFd = -1;
    for (std::map<int, std::string>::const_iterator it = clientNick.begin(); it != clientNick.end(); ++it)
    {
        if (it->second == target)
        {
            targetFd = it->first;
            break;
        }
    }

    if (targetFd == -1)
        return;

    std::string line = ":" + clientNick[clientFd] + "!user@host PRIVMSG " + target + " :" + message;
    server->queueSend(targetFd, line);
}

void ProtocolManager::disconnectClient(int clientFd)
{
    server->disconnectFd(clientFd);
}


void ProtocolManager::sendResponse(int clientFd, const std::string &response)
{
    server->queueSend(clientFd, response);
}

void ProtocolManager::sendNumericResponse(int clientFd, int code, const std::string &nickname, const std::string &message)
{
    std::ostringstream oss;

    oss << ":server ";
    if (code < 10) {
        oss << "00";
    }
    else if (code < 100) {
        oss << "0";
    }
    oss << code << " " << nickname << " :" << message;
    server->queueSend(clientFd, oss.str());
}