#include "../../include/Channel.hpp"

// CHANNEL MODE
bool Channel::getChannelMode(std::string input){
    std::list<std::string>::iterator it = this->channelMode.begin();
    while(it != this->channelMode.end()){
        if(*it == input)
            return true;
        it++;
    }
    return false;
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
// CHANNEL MODE END

std::list<Channel>::iterator getChannel(std::list<Channel> &channelList, std::string channel){
    std::list<Channel>::iterator it = channelList.begin();
    while(it != channelList.end()){
        if(it->getName() == channel)
            return it;
        it++;
    }
    return channelList.end();
}