#include "../../include/Channel.hpp"

// CLIENT LIST 
void Channel::addClientList(int fd){
    this->clientList.push_back(fd);
}

void Channel::removeClientList(int fd){
    std::list<int>::iterator it = this->clientList.begin();
    while(it != clientList.end()){
        if(*it == fd)
            break;
        it++;
    }
    if(it != this->clientList.end())
        this->clientList.erase(it);
}

bool Channel::checkClient(int fd){
    std::list<int>::iterator find = this->clientList.begin();
    std::list<int>::iterator it = this->clientList.end();
    while(find != it){
        if(*find == fd)
            return true;
        find++;
    }
    return false;
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
        us = userList.find(*this->clientList.begin());
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


