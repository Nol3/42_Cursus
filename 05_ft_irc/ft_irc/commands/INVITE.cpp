#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::INVITEcmd(int clientFd, const IRCMsg &message)
{
    if (message.params.size() < 2) return;

    std::string target_nick = message.params[0];
    std::string channel = message.params[1];

    if (channel[0] != '#') 
    {
        channel = "#" + channel;
    }

    if (server->getChannelClients(channel).empty()) {
        sendNumericResponse(clientFd, 403, channel, "No such channel");
        return;
    }

    std::set<int> channel_clients = server->getChannelClients(channel);
    if (channel_clients.find(clientFd) == channel_clients.end()) {
        sendNumericResponse(clientFd, 442, channel, "You're not on that channel");
        return;
    }

    if (!server->isChannelOperator(clientFd, channel)) {
        sendNumericResponse(clientFd, 482, channel, "You're not channel operator");
        return;
    }

    int target_fd = -1;
    std::map<int, std::string> all_nicks = server->getAllNicknames();
    for (std::map<int, std::string>::iterator it = all_nicks.begin(); it != all_nicks.end(); ++it) {
        if (it->second == target_nick) {
            target_fd = it->first;
            break;
        }
    }

    if (target_fd == -1) {
        sendNumericResponse(clientFd, 401, target_nick, "No such nick/channel");
        return;
    }

    if (channel_clients.find(target_fd) != channel_clients.end()) {
        sendNumericResponse(clientFd, 443, target_nick + " " + channel, "is already on channel");
        return;
    }

    server->addChannelInvite(channel, target_fd);
    sendNumericResponse(clientFd, 341, target_nick + " " + channel, "");

    std::string inviter_nick = server->getClientNick(clientFd);
    server->queueSend(target_fd, ":" + inviter_nick + "!user@host INVITE " + target_nick + " " + channel);
}