#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"
#include <sstream>
#include <cstdlib>

ProtocolManager::IRCMsg ProtocolManager::parseMessage(const std::string &rawMsg)
{
    IRCMsg msg;
    std::string s = rawMsg;

    if (!s.empty() && s[0] == ':') 
    {
        std::string::size_type sp = s.find(' ');
        if (sp != std::string::npos) 
        {
            msg.prefix = s.substr(1, sp - 1);
            s.erase(0, sp + 1);
        } 
        else 
        {
            msg.prefix = s.substr(1);
            s.clear();
        }
    }

    std::string::size_type colon = s.find(" :");
    if (colon != std::string::npos) 
    {
        msg.trailing = s.substr(colon + 2);
        s.erase(colon);
    }

    std::string::size_type sp = s.find(' ');
    if (sp == std::string::npos) 
    {
        msg.command = s;
        s.clear();
    } 
    else 
    {
        msg.command = s.substr(0, sp);
        s.erase(0, sp + 1);
    }

    while (!s.empty()) 
    {
        std::string::size_type sp2 = s.find(' ');
        if (sp2 == std::string::npos) 
        {
            msg.params.push_back(s);
            break;
        }
         else 
         {
            msg.params.push_back(s.substr(0, sp2));
            s.erase(0, sp2 + 1);
        }
    }

    return msg;
}

bool ProtocolManager::isNicknameInUse(const std::string& nick) const {
    for (std::map<int, std::string>::const_iterator it = clientNick.begin();
         it != clientNick.end(); ++it) {
        if (it->second == nick) {
            return true;
        }
    }
    return false;
}

ProtocolManager::ProtocolManager(irce *serverRef) : server(serverRef)
{
    commandHandlers["NICK"] = &ProtocolManager::NICKcmd;
    commandHandlers["USER"] = &ProtocolManager::USERcmd;
    commandHandlers["PASS"] = &ProtocolManager::PASScmd;
    commandHandlers["JOIN"] = &ProtocolManager::JOINcmd;
    commandHandlers["PRIVMSG"] = &ProtocolManager::PRIVMSGcmd;
    commandHandlers["NOTICE"] = &ProtocolManager::NOTICEcmd;
    commandHandlers["KICK"] = &ProtocolManager::KICKcmd;
    commandHandlers["INVITE"] = &ProtocolManager::INVITEcmd;
    commandHandlers["TOPIC"] = &ProtocolManager::TOPICcmd;
    commandHandlers["MODE"] = &ProtocolManager::MODEcmd;
    commandHandlers["PING"] = &ProtocolManager::PINGcmd;
    commandHandlers["QUIT"] = &ProtocolManager::QUITcmd;
}

ProtocolManager::~ProtocolManager(){}

void ProtocolManager::processCommand(int clientFd, const std::string &input)
{
	IRCMsg msg = parseMessage(input);

	if (msg.command == "PASS") {
		PASScmd(clientFd, msg);
		return;
	}
	if (!server->isPassOk(clientFd) && !server->isPasswordEmpty()) {
		sendNumericResponse(clientFd, 451, "*", "You have not registered");
		return;
	}

    if (msg.command == "NICK" || msg.command == "USER") {
        std::map<std::string, CommandHandler>::iterator it = commandHandlers.find(msg.command);
        if (it != commandHandlers.end()) {
            CommandHandler h = it->second;
            (this->*h)(clientFd, msg);
        }
        return;
    }

    if (!server->isRegistered(clientFd)) {
        sendNumericResponse(clientFd, 451, "*", "You have not registered");
        return;
    }

	std::map<std::string, CommandHandler>::iterator it = commandHandlers.find(msg.command);
	if (it != commandHandlers.end()) {
		CommandHandler h = it->second;
		(this->*h)(clientFd, msg);
	}
}

void ProtocolManager::onClientDisconnected(int clientFd)
{
    clientNick.erase(clientFd);
    clientHasUser.erase(clientFd);
}

void ProtocolManager::tryCompleteRegistration(int clientFd)
{
    if (clientNick[clientFd].empty()) return;
    if (!clientHasUser[clientFd]) return;
    if (!server->isPassOk(clientFd)) return;

    if (server->isRegistered(clientFd)) return;

    std::string nick = clientNick[clientFd];
    sendNumericResponse(clientFd, 001, nick, "Welcome to the IRC server " + nick);
    server->markRegistered(clientFd, true);
}