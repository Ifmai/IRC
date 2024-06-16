#include "../../include/Channel.hpp"

Channel::Channel(std::string name, std::string type, int clientFd){
    this->channelName = name;
    this->channelType = type;
    this->clientList.push_back(clientFd);
    this->channelKey = "";
    this->isPublic = true;
    this->isInvite = false;
    this->keyExist = false;
    //eklemeler yapılcak bunların hepsine channela baya bir şey ekledim.
}

Channel::Channel(const Channel& copy){
    this->channelName = copy.channelName;
    this->channelType = copy.channelType;
    this->channelMode = copy.channelMode;
    this->channelKey = copy.channelKey;
    this->clientList = copy.clientList;
    this->inviteList = copy.inviteList;
    this->channelModerator = copy.channelModerator;
    this->isPublic = copy.isPublic;
    this->isInvite = copy.isInvite;
    this->keyExist = copy.keyExist;
}

Channel& Channel::operator=(const Channel& copy){
    if(this == &copy)
        return *this;
    this->channelName = copy.channelName;
    this->channelType = copy.channelType;
    this->channelMode = copy.channelMode;
    this->channelKey = copy.channelKey;
    this->clientList = copy.clientList;
    this->inviteList = copy.inviteList;
    this->channelModerator = copy.channelModerator;
    this->isPublic = copy.isPublic;
    this->isInvite = copy.isInvite;
    this->keyExist = copy.keyExist;

    return *this;
}

Channel::~Channel(){}

std::string Channel::getName(){
    return this->channelName;
}

std::string Channel::getChannelType(){
    return this->channelType;
}

bool Channel::getChannelMode(std::string input){
    std::list<std::string>::iterator it = this->channelMode.begin();
    while(it != this->channelMode.end()){
        if(*it == input)
            return true;
        it++;
    }
    return false;
}

bool Channel::getisInvite(){
    return this->isInvite;
}

std::string Channel::getKey(){
    return this->channelKey;
}

void Channel::setKey(std::string input){
    this->channelKey = input;
}

bool Channel::getKeyExist(){
    return this->keyExist;
}

void Channel::setKeyExist(bool input){
    this->keyExist = input;
}

void Channel::addChannelMode(std::string input){
    this->channelMode.push_back(input);
}

void Channel::removeChannelMode(std::string input){
    std::list<std::string>::iterator find = this->channelMode.begin();
    while(find != this->channelMode.end()){
        if(*find == input){
            this->channelMode.erase(find);
            return;
        }
        find++;
    }
}

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

bool checkList(std::string channel, std::list<Channel> &channelList){
    std::list<Channel>::iterator it = channelList.begin();
    while(it != channelList.end()){
        if(it->getName() == channel)
            return true;
        it++;
    }
    return false;
}

std::list<Channel>::iterator getChannel(std::list<Channel> &channelList, std::string channel){
    std::list<Channel>::iterator it = channelList.begin();
    while(it != channelList.end()){
        if(it->getName() == channel)
            return it;
        it++;
    }
    return channelList.end();
}

bool Channel::getIsPublic(){
    return this->isPublic;
}

void Channel::setIsPublic(bool input){
    this->isPublic = input;
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

void Channel::addInviteList(int fd){
    this->inviteList.push_back(fd);
}

std::string Channel::getTopic(){
    return this->channelTopic;
}

void Channel::setTopic(std::string newTopic){
    this->channelTopic = newTopic;
}

std::string Channel::getChangerTopic(){
    return this->changerTopic;
}

void Channel::setChangerTopic(std::string nick){
    this->changerTopic = nick;
}

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

int Channel::getClientListSize(){
    return this->clientList.size();
}

void Channel::checkModerator(std::map<int, User> &userList){
    std::cout << "selam bro" << std::endl;
    if(this->clientList.size() > 0 && this->channelModerator.size() == 0){
        // atama yapmıyor.
        std::map<int, User>::iterator us;
        std::string modeMsg;
        us = userList.find(*this->clientList.begin());
        std::cout << us->second.getClientSocket() << " " << us->second.gethostInfo() << std::endl;
        modeMsg = us->second.getIDENTITY() + " MODE " + this->getName() + " +o " + us->second.getName(USER_NICK_NAME) + "\r\n";
        std::cout << "MODE MSH: " << modeMsg << std::endl;
    }
}