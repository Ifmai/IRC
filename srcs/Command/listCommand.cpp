#include "../../include/IRC.hpp"

static std::string writeList(std::list<Channel> &channelList, int count, char token){
    std::string listChannel;
    std::list<Channel>::iterator ch = channelList.begin();
    while(ch != channelList.end()){
        if(ch->getClientListSize() >= count && token == '>')
            listChannel += ch->getName() + "\n";
        else if (ch->getClientListSize() <= count && token == '<')
            listChannel += ch->getName() + "\n";
        ch++;
    }
    return listChannel;
}

static bool isNumeric(const std::string& str) {
    for(size_t i = 0; i < str.length(); i++) {
        if (!std::isdigit(str.at(i)))
            return false;
    }
    return true;
}

void commandList(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
    std::string channel;

    if(iss >> channel){
        std::list<Channel>::iterator ch;
        if(channel.at(0) == '>'){
            char token = channel.at(0);
            channel.erase(0, 1);
            if(isNumeric(channel)){
                int count = std::stoi(channel);
                std::string sendMsg = writeList(channelList, count, token);
                if(sendMsg.empty())
                    sendMsg = "No suitable channel found\r\n";
                else
                    sendMsg.append("\r\n");
                messageSend(user.getClientSocket(), sendMsg);
            }else
                messageSend(user.getClientSocket(), ">4, ONLY NUMBER\r\n");
        }else if(channel.at(0) == '#' || channel.at(0) == '&'){
            ch = getChannel(channelList, channel);
            ch->writeClientList(user.getClientSocket(), userList);
        }
    }else{
        std::string token = "LIST";
        messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
    }
}