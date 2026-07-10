#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::USERcmd(int clientFd, const IRCMsg &message)
{
    std::string nick;
    std::string user;
    std::string host;
    std::string port;

    if (server->isRegistered(clientFd))
    {
        sendNumericResponse(clientFd, 462, "USER", "You are already registered");
        return;
    }

    if (message.params.size() == 4 && message.trailing.empty())
    {
        user = message.params[3];
    }

    else if (message.params.size() < 3) 
	{
        sendNumericResponse(clientFd, 461, "USER", "Not enough parameters");
        return;
    }

    nick = message.params[0];
    host = message.params[1];
    port = message.params[2];

    if (!message.trailing.empty())
        user = message.trailing;
	
    int ret = server->setUser(clientFd, nick, user, host, port);
    switch (ret)
    {
        case -1:
            sendNumericResponse(clientFd, 422, "USER", "You're yet to register");
            return;
        case 1:
            sendNumericResponse(clientFd, 433, nick, "Nickname is already in use");
            return;
        case 2:
            sendNumericResponse(clientFd, 462, nick, "Username is already in use");
            return;
        case 0:
            break;
    }

    clientHasUser[clientFd] = true;
    tryCompleteRegistration(clientFd);
}