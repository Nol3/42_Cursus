#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"


void ProtocolManager::PASScmd(int clientFd, const IRCMsg &message)
{
    std::string pass;
    if (!message.params.empty()) pass = message.params[0];

    else pass = message.trailing;

    if (server->isPasswordEmpty()) {
        server->markPassOk(clientFd, true);
        tryCompleteRegistration(clientFd);
        return;
    }

    if (server->isPasswordValid(pass)) {
        server->markPassOk(clientFd, true);
        tryCompleteRegistration(clientFd);
    } 
	else 
	{
        sendNumericResponse(clientFd, 464, "*", "Password incorrect");
        server->disconnectFd(clientFd);
    }
}