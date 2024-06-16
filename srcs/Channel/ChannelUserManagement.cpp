#include "../../include/Channel.hpp"

// CLIENT LIST 
void Channel::addClientList(int fd){
    this->clientList.insert(std::pair<int, bool>(fd,false));
}

void Channel::removeClientList(int fd){
    std::map<int, bool>::iterator it;
    
    it = this->clientList.find(fd);
    if(it != this->clientList.end())
        this->clientList.erase(it);
}

bool Channel::checkClient(int fd){
    std::map<int, bool>::iterator it;

    it = this->clientList.find(fd);
    if(it != this->clientList.end())
        return true;
    return false;
}

bool Channel::getJoinChannel(int fd){
    return (this->clientList.find(fd))->second;
}

void Channel::setJoinChannel(int fd){
    std::map<int, bool>::iterator it;

    it = this->clientList.find(fd);
    it->second = true;
}
// CLIENT LIST END.

// CHANNEL MODERATOR
void Channel::addModerator(int fd){
    this->channelModerator.push_back(fd);
}

void Channel::removeModerator(int fd){
    std::list<int>::iterator find = this->channelModerator.begin();
    while(find != this->channelModerator.end()){
        if(*find == fd){
            this->channelModerator.erase(find);
            return;
        }
        find++;
    }
}

bool Channel::checkClientMode(int fd){
    std::list<int>::iterator find = this->channelModerator.begin();
    std::list<int>::iterator it = this->channelModerator.end();
    while(find != it){
        if(*find == fd)
            return true;
        find++;
    }
    return false;
}

void Channel::ensureModeratorPresence(std::map<int, User> &userList){
    if(this->channelModerator.size() == 0){
        std::map<int, User>::iterator us;
        us = userList.find((this->clientList.begin())->first);
        this->addModerator(us->second.getClientSocket());
        this->sendAllMsg(us->second.getIDENTITY() + " MODE " + this->getName() + " +o " + us->second.getName(USER_NICK_NAME) + "\r\n");
    }
}
// MODERATOR END

// INVITE
void Channel::addInviteList(int fd){
    this->inviteList.push_back(fd);
}

void Channel::removeInviteList(int fd){
    std::list<int>::iterator it = this->inviteList.begin();
    while(it != inviteList.end()){
        if(*it == fd)
            break;
        it++;
    }
    if(it != this->inviteList.end())
        this->inviteList.erase(it);
}

bool Channel::getInviteList(int fd){
    std::list<int>::iterator find = this->inviteList.begin();
    std::list<int>::iterator it = this->inviteList.end();
    while(find != it){
        if(*find == fd)
            return true;
        find++;
    }
    return false;
}
// INVITE END


