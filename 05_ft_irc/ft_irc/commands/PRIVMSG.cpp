#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::PRIVMSGcmd(int clientFd, const IRCMsg &message)
{
    if (message.params.empty()) return;

    std::string target = message.params[0];
    std::string text = message.trailing;
    
    if (text.empty() && message.params.size() >= 2) text = message.params[1];

    std::string nick = clientNick[clientFd];

    std::string line = ":" + (nick.empty() ? std::string("*") : nick) + "!user@host PRIVMSG " + target + " :" + text;

    if (!target.empty() && target[0] == '#') {
        std::set<int> members = server->getChannelClients(target);
        
        if (members.empty()) {
            sendNumericResponse(clientFd, 403, nick, target + " :No such channel");
            return;
        }
        
        if (members.find(clientFd) == members.end()) {
            sendNumericResponse(clientFd, 442, nick, target + " :You're not on that channel");
            return;
        }
        
        server->broadcastToChannel(clientFd, target, line);
    }
    else {
        int target_fd = -1;
        for (std::map<int, std::string>::const_iterator it = clientNick.begin(); 
                it != clientNick.end(); ++it) {
            if (it->second == target) {
                target_fd = it->first;
                break;
            }
        }
        
        if (target_fd == -1) {
            sendNumericResponse(clientFd, 401, nick, target + " :No such nick/channel");
            return;
        }

        server->queueSend(target_fd, line);
    }
}