#include "../include/irce.hpp"

//==============================================================================//
//                              GETTERS&SETTERS                                 //
//==============================================================================//

std::string irce::getChannelKey(const std::string& channel_name) const {
    std::map<std::string, std::string>::const_iterator it = channelKeys.find(channel_name);
    if (it == channelKeys.end()) return "";
    return it->second;
}

void irce::setChannelKey(const std::string& channel_name, const std::string& key) {
    if (key.empty()) {
        channelKeys.erase(channel_name);
    } else {
        channelKeys[channel_name] = key;
    }
}

std::string irce::getChannelTopic(const std::string& channel_name) const {
    std::map<std::string, std::string>::const_iterator it = channelTopics.find(channel_name);
    if (it == channelTopics.end()) return "";
    return it->second;
}

void irce::setChannelTopic(const std::string& channel_name, const std::string& topic) {
    channelTopics[channel_name] = topic;
}

int irce::getChannelLimit(const std::string& channel_name) const {
    std::map<std::string, int>::const_iterator it = channelLimits.find(channel_name);
    if (it == channelLimits.end()) return -1;
    return it->second;
}

void irce::setChannelLimit(const std::string& channel_name, int limit) {
    if (limit <= 0) {
        channelLimits.erase(channel_name);
    } else {
        channelLimits[channel_name] = limit;
    }
}

//================================================================================//
//                            CAMBIOS DE MODO                                     //
//================================================================================//

bool irce::isChannelInviteOnly(const std::string& channel_name) const {
    std::map<std::string, bool>::const_iterator it = channelInviteOnly.find(channel_name);
    return it != channelInviteOnly.end() && it->second;
}

void irce::setChannelInviteOnly(const std::string& channel_name, bool value) {
    channelInviteOnly[channel_name] = value;
}

bool irce::isChannelTopicProtected(const std::string& channel_name) const {
    std::map<std::string, bool>::const_iterator it = channelTopicProtected.find(channel_name);
    return it != channelTopicProtected.end() && it->second;
}

void irce::setChannelTopicProtected(const std::string& channel_name, bool value) {
    channelTopicProtected[channel_name] = value;
}

void irce::addChannelInvite(const std::string& channel_name, int client_fd) {
    channelInvites[channel_name].insert(client_fd);
}

void irce::removeChannelInvite(const std::string& channel_name, int client_fd) {
    std::map<std::string, std::set<int> >::iterator it = channelInvites.find(channel_name);
    if (it != channelInvites.end()) {
        it->second.erase(client_fd);
    }
}

//================================================================================//
//                            MANEJO DE OPERADORES                                //
//================================================================================//

bool irce::isChannelOperator(int client_fd, const std::string& channel_name) const {
    std::map<std::string, std::set<int> >::const_iterator it = channelOperators.find(channel_name);
    if (it == channelOperators.end()) return false;
    return it->second.find(client_fd) != it->second.end();
}

void irce::addChannelOperator(const std::string& channel_name, int client_fd) {
    channelOperators[channel_name].insert(client_fd);
}

void irce::removeChannelOperator(const std::string& channel_name, int client_fd) {
    std::map<std::string, std::set<int> >::iterator it = channelOperators.find(channel_name);
    if (it != channelOperators.end()) {
        it->second.erase(client_fd);
    }
}

//================================================================================//
//                            MANEJO DE USUARIOS                                  //
//================================================================================//

bool irce::isUserInvited(const std::string& channel_name, int client_fd) {
    std::map<std::string, std::set<int> >::iterator it = channelInvites.find(channel_name);
    if (it == channelInvites.end()) return false;
    return it->second.find(client_fd) != it->second.end();
}

std::set<int> irce::getChannelClients(const std::string& channel_name) const {
    std::map<std::string, std::set<int> >::const_iterator it = channels.find(channel_name);
    if (it == channels.end()) return std::set<int>();
    return it->second;
}

void irce::joinChannel(int client_fd, const std::string& channel_name) {
    if (channels[channel_name].empty()) {
        channelOperators[channel_name].insert(client_fd);
        channelTopicProtected[channel_name] = true;
    }

    channels[channel_name].insert(client_fd);
    queueSend(client_fd, ":server JOIN " + channel_name);

    if (channelOperators[channel_name].find(client_fd) != channelOperators[channel_name].end()) {
        queueSend(client_fd, ":server MODE " + channel_name + " +o " + clients[client_fd].nickname);
    }
}

bool irce::addClientToChannel(int client_fd, const std::string& channel_name, const std::string& key) {
    int limit = getChannelLimit(channel_name);
    if (limit > 0 && (int)channels[channel_name].size() >= limit) {
        queueSend(client_fd, ":server 471 " + clients[client_fd].nickname + " " + channel_name + " :Cannot join channel (+l)");
        return false;
    }

    std::string channel_key = getChannelKey(channel_name);
    if (!channel_key.empty() && channel_key != key) {
        queueSend(client_fd, ":server 475 " + clients[client_fd].nickname + " " + channel_name + " :Cannot join channel (+k)");
        return false;
    }

    if (isChannelInviteOnly(channel_name)) {
        if (!isUserInvited(channel_name, client_fd)) {
            queueSend(client_fd, ":server 473 " + clients[client_fd].nickname + " " + channel_name + " :Cannot join channel (+i)");
            return false;
        }
        removeChannelInvite(channel_name, client_fd);
    }

    joinChannel(client_fd, channel_name);
    return true;
}

void irce::removeClientFromChannel(int client_fd, const std::string& channel_name) {
    std::map<std::string, std::set<int> >::iterator it = channels.find(channel_name);
    if (it != channels.end()) {
        it->second.erase(client_fd);
    }
    std::map<std::string, std::set<int> >::iterator opIt = channelOperators.find(channel_name);
    if (opIt != channelOperators.end()) {
        opIt->second.erase(client_fd);
    }
}

//================================================================================//
//                            BROADCASTING                                        //
//================================================================================//

void irce::broadcastToChannel(int client_fd, const std::string& channel_name, const std::string& rawLine) {
    std::map<std::string, std::set<int> >::iterator it = channels.find(channel_name);
    if (it == channels.end()) return;
    const std::set<int> &members = it->second;
    for (std::set<int>::const_iterator mit = members.begin(); mit != members.end(); ++mit) {
        int to_fd = *mit;
        if (to_fd == client_fd) continue;
        queueSend(to_fd, rawLine);
    }
}