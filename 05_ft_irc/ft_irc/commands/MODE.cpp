#include "../include/ProtocolManager.hpp"
#include "../include/irce.hpp"

void ProtocolManager::MODEcmd(int clientFd, const IRCMsg &message)
{
    if (message.params.empty()) return;

    std::string target = message.params[0];

    if (target[0] != '#') {
        target = "#" + target;
    }

    if (server->getChannelClients(target).empty()) {
        sendNumericResponse(clientFd, 403, target, "No such channel");
        return;
    }

    if (message.params.size() < 2) {
        sendNumericResponse(clientFd, 461, target, "MODE :Not enough parameters");
        return;
    }

    std::set<int> channel_clients = server->getChannelClients(target);
    if (channel_clients.find(clientFd) == channel_clients.end()) {
        sendNumericResponse(clientFd, 442, target, "You're not on that channel");
        return;
    }

    if (!server->isChannelOperator(clientFd, target)) {
        sendNumericResponse(clientFd, 482, target, "You're not channel operator");
        return;
    }

    std::string modes = message.params[1];
    size_t param_index = 2;
    bool adding = true;
    std::string mode_changes;
    std::string mode_params;

    for (size_t i = 0; i < modes.length(); ++i) {
        char mode = modes[i];

        if (mode == '+') {
            adding = true;
            continue;
        } else if (mode == '-') {
            adding = false;
            continue;
        }

        switch (mode) {
            case 'i':
                server->setChannelInviteOnly(target, adding);
                mode_changes += (adding ? "+" : "-");
                mode_changes += "i";
                break;

            case 't':
                server->setChannelTopicProtected(target, adding);
                mode_changes += (adding ? "+" : "-");
                mode_changes += "t";
                break;

            case 'k':
                if (adding) {
                    if (param_index < message.params.size()) {
                        std::string key = message.params[param_index++];
                        server->setChannelKey(target, key);
                        mode_changes += "+k";
                        mode_params += " " + key;
                    }
                } else {
                    server->setChannelKey(target, "");
                    mode_changes += "-k";
                }
                break;

            case 'o':
                if (param_index < message.params.size()) {
                    std::string target_nick = message.params[param_index++];

                    int target_fd = -1;
                    std::map<int, std::string> all_nicks = server->getAllNicknames();
                    for (std::map<int, std::string>::iterator it = all_nicks.begin(); it != all_nicks.end(); ++it) {
                        if (it->second == target_nick) {
                            target_fd = it->first;
                            break;
                        }
                    }

                    if (target_fd != -1 && channel_clients.find(target_fd) != channel_clients.end()) {
                        if (adding) {
                            server->addChannelOperator(target, target_fd);
                        } else {
                            server->removeChannelOperator(target, target_fd);
                        }
                        mode_changes += (adding ? "+" : "-");
                        mode_changes += "o";
                        mode_params += " " + target_nick;
                    }
                }
                break;

            case 'l':
                if (adding) {
                    if (param_index < message.params.size()) {
                        std::string limit_str = message.params[param_index++];
                        int limit = atoi(limit_str.c_str());
                        if (limit > 0) {
                            server->setChannelLimit(target, limit);
                            mode_changes += "+l";
                            mode_params += " " + limit_str;
                        }
                    }
                } else {
                    server->setChannelLimit(target, -1);
                    mode_changes += "-l";
                }
                break;

            default:
                break;
        }
    }
    
    if (!mode_changes.empty()) {
        std::string client_nick = server->getClientNick(clientFd);
        std::string mode_msg = ":" + client_nick + "!user@host MODE " + target + " " + mode_changes + mode_params;
        server->broadcastToChannel(clientFd, target, mode_msg);
        server->queueSend(clientFd, mode_msg);
    }
}