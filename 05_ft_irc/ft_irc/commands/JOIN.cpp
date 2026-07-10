#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::JOINcmd(int clientFd, const IRCMsg &message)
{
    if (message.params.empty() && message.trailing.empty()) return;
	
    std::string channel = message.params.empty() ? message.trailing : message.params[0];

    if (channel.empty()) return;

    if (channel[0] != '#') 
	{
        channel = "#" + channel;
    }
    if (channel[0] == '#' && channel.size() <= 1)
    {
        sendNumericResponse(clientFd, 403, channel, "Cannot join empty channel");
        return;
    }
    std::string key = "";
    if (message.params.size() >= 2) {
        key = message.params[1];
    }

    server->addClientToChannel(clientFd, channel, key);
}