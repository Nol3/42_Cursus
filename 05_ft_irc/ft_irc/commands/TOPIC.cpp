#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::TOPICcmd(int clientFd, const IRCMsg &message)
{
    if (message.params.empty()) return;

    std::string channel = message.params[0];

    if (channel[0] != '#') {
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

    if (message.trailing.empty()) {
        std::string current_topic = server->getChannelTopic(channel);
        if (current_topic.empty()) {
            sendNumericResponse(clientFd, 331, channel, "No topic is set");
        } else {
            sendNumericResponse(clientFd, 332, channel, current_topic);
        }
        return;
    }

    if (server->isChannelTopicProtected(channel)) {
        if (!server->isChannelOperator(clientFd, channel)) {
            std::string nick = server->getClientNick(clientFd);
            sendNumericResponse(clientFd, 482, nick + " " + channel, "You're not channel operator");
            return;
        }
    }

    server->setChannelTopic(channel, message.trailing);

    std::string client_nick = server->getClientNick(clientFd);
    std::string topic_msg = ":" + client_nick + "!user@host TOPIC " + channel + " :" + message.trailing;
    server->broadcastToChannel(clientFd, channel, topic_msg);
    server->queueSend(clientFd, topic_msg); // También al que lo cambió
}