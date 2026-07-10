#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::NOTICEcmd(int clientFd, const IRCMsg &message)
{
    if (message.params.empty()) return;

    std::string target = message.params[0];
    std::string text = message.trailing;

    if (text.empty() && message.params.size() >= 2) text = message.params[1];

    std::string nick = clientNick[clientFd];
    if (nick.empty()) return;

    std::string line = ":" + nick + "!user@host NOTICE " + target + " :" + text;

    if (!target.empty() && target[0] == '#') 
	{
        server->broadcastToChannel(clientFd, target, line);
    }
    else 
	{
        bool found = false;
        for (std::map<int, std::string>::const_iterator it = clientNick.begin(); it != clientNick.end(); ++it) 
        {
            if (it->second == target) {
                server->queueSend(it->first, line);
                found = true;
                break;
            }
        }
        (void)found;
    }
}