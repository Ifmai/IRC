#include "../../include/Channel.hpp"

Channel::Channel(std::string name, std::string type, std::string key, int clientFd){
    this->channelName = name;
    this->channelType = type;
    this->channelKey = key;
    this->clientList.push_back(clientFd);
}

Channel::Channel(const Channel& copy){
    this->channelName = copy.channelName;
    this->channelType = copy.channelType;
    this->channelMode = copy.channelMode;
    this->clientList = copy.clientList;
}

Channel& Channel::operator=(const Channel& copy){
    if(this == &copy)
        return *this;
    this->channelName = copy.channelName;
    this->channelType = copy.channelType;
    this->channelMode = copy.channelMode;
    this->clientList = copy.clientList;
}

Channel::~Channel(){}

std::string Channel::getName(){
    return this->channelName;
}

std::string Channel::getChannelType(){
    return this->channelType;
}

/* std::string Channel::getChannelMode(){
    return this->channelMode;
} */

bool Channel::getisInvite(){
    return this->isInvite;
}

bool Channel::checkClient(int fd){
    std::list<int>::iterator find = this->clientList.begin();
    std::list<int>::iterator it = this->clientList.end();
    while(find != it){
        if(*find == fd)
            return true;
        find++;
    }
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

