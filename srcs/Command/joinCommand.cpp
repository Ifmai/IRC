#include "../../include/IRC.hpp"

static void createChannel(std::string channelName, std::string key, std::list<Channel> &channelList, User &user){
    std::string key;
    if(!key.empty()){
        if(channelName.at(0) == '#')
            channelList.push_back(Channel(channelName, "#", key, user.getClientSocket()));
        else if(channelName.at(0) == '&')
            channelList.push_back(Channel(channelName, "&", key, user.getClientSocket()));
    }else{
        if(channelName.at(0) == '#')
            channelList.push_back(Channel(channelName, "#", user.getClientSocket())); // Buna emin değilim doğru çalışacak mı?
        else if(channelName.at(0) == '&')
            channelList.push_back(Channel(channelName, "&", user.getClientSocket())); // Buna emin değilim doğru çalışacak mı?
    }
}

void commandJoin(std::string buff, std::istringstream &iss, std::list<Channel> &channelList, User &user){
    std::string channel;
    if(iss >> channel){
        std::string key = "";
        iss >> key;
        if(!checkList(channel, channelList))
            createChannel(channel, key, channelList, user);
        std::list<Channel>::iterator it = getChannel(channelList, channel);
        
    }
    //else yetersiz arguman error msg
}

