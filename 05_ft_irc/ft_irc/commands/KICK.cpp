#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::KICKcmd(int clientFd, const IRCMsg &message)
{
    if (message.params.size() < 2) {
        sendNumericResponse(clientFd, 461, clientNick[clientFd], "KICK :Not enough parameters");
        return;
    }

    std::string channel = message.params[0];
    std::string targetNick = message.params[1];
    std::string reason = message.trailing;
    if (reason.empty()) reason = clientNick[clientFd];

    if (channel.empty() || channel[0] != '#') {
        sendNumericResponse(clientFd, 403, clientNick[clientFd], channel + " :No such channel");
        return;
    }

    if (!server->isChannelOperator(clientFd, channel)) {
        sendNumericResponse(clientFd, 482, clientNick[clientFd], channel + " :You're not channel operator");
        return;
    }

    int targetFd = -1;
    for (std::map<int, std::string>::const_iterator it = clientNick.begin(); it != clientNick.end(); ++it) {
        if (it->second == targetNick) {
            targetFd = it->first;
            break;
        }
    }

    if (targetFd == -1) {
        sendNumericResponse(clientFd, 401, clientNick[clientFd], targetNick + " :No such nick");
        return;
    }

    std::set<int> channel_clients = server->getChannelClients(channel);
    if (channel_clients.find(targetFd) == channel_clients.end()) {
        sendNumericResponse(clientFd, 442, clientNick[clientFd], channel + " :the client is not on that channel");
        return;
    }
    std::string kickMsg = ":" + clientNick[clientFd] + "!user@host KICK " + channel + " " + targetNick + " :" + reason;

    server->broadcastToChannel(clientFd, channel, kickMsg);
    server->queueSend(targetFd, kickMsg);
    server->queueSend(clientFd, kickMsg);

    server->removeClientFromChannel(targetFd, channel);
}