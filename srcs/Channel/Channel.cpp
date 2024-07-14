#include "../../include/Channel.hpp"

Channel::Channel(std::string name, std::string type, int clientFd){
    this->channelName = name;
    this->channelType = type;
    this->channelKey = "";
    this->clientList.insert(std::pair<int, bool>(clientFd, false));
    this->channelTopic = "";
    this->changerTopic = "";
    this->isPublic = true;
    this->isInvite = false;
    this->keyExist = false;
}

Channel::Channel(const Channel& copy){
    this->channelName = copy.channelName;
    this->channelType = copy.channelType;
    this->channelMode = copy.channelMode;
    this->channelKey = copy.channelKey;
    this->clientList = copy.clientList;
    this->inviteList = copy.inviteList;
    this->channelModerator = copy.channelModerator;
    this->channelTopic = copy.channelTopic;
    this->changerTopic = copy.changerTopic;
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
    this->channelTopic = copy.channelTopic;
    this->changerTopic = copy.changerTopic;
    this->isPublic = copy.isPublic;
    this->isInvite = copy.isInvite;
    this->keyExist = copy.keyExist;

    return *this;
}

Channel::~Channel(){}


// Getter
std::string Channel::getName(){
    return this->channelName;
}

std::string Channel::getChannelType(){
    return this->channelType;
}

bool Channel::getisInvite(){
    return this->isInvite;
}

bool Channel::getKeyExist(){
    return this->keyExist;
}

bool Channel::getIsPublic(){
    return this->isPublic;
}

std::string Channel::getKey(){
    return this->channelKey;
}

std::string Channel::getTopic(){
    return this->channelTopic;
}

std::string Channel::getChangerTopic(){
    return this->changerTopic;
}

int Channel::getClientListSize() const{
    return this->clientList.size();
}


// Setter
void Channel::setKey(std::string input){
    this->channelKey = input;
}

void Channel::setKeyExist(bool input){
    this->keyExist = input;
}

void Channel::setIsPublic(bool input){
    this->isPublic = input;
}

void Channel::setTopic(std::string newTopic){
    this->channelTopic = newTopic;
}

void Channel::setChangerTopic(std::string nick){
    this->changerTopic = nick;
}
