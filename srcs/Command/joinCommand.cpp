#include "../../include/IRC.hpp"

static void createChannel(std::string channelName, std::string key, std::list<Channel> &channelList, User &user){
    std::string joinMsg;
    std::string modeMsg;
    std::string userIdentity = user.getIDENTITY();
    if(channelName.at(0) == '#')
        channelList.push_back(Channel(channelName, "#", user.getClientSocket()));
    else if(channelName.at(0) == '&')
        channelList.push_back(Channel(channelName, "&", user.getClientSocket()));
    std::list<Channel>::iterator it = getChannel(channelList, channelName);
    it->addModerator(user.getClientSocket());
    messageSend(user.getClientSocket(), userIdentity + " JOIN " + channelName + "\r\n");
    messageSend(user.getClientSocket(), "MODE " + channelName +  " +o " + user.getName(USER_NICK_NAME) + "\r\n");
    if(!key.empty()){
        it->setKeyExist(true);
        it->setKey(key);
        it->addChannelMode("+k");
        messageSend(user.getClientSocket(),userIdentity + " MODE " + channelName +  " +k " + key + "\r\n");
    }
}

static void sendTopic(std::list<Channel>::iterator &it, User &user){
    std::string topic = it->getTopic();
    if(!topic.empty())
        messageSend(user.getClientSocket(), RPL_TOPIC(it->getChangerTopic(), it->getName(), topic));
    else
        messageSend(user.getClientSocket(), RPL_NOTOPIC(it->getName()));
}

void commandJoin(std::istringstream &iss, std::list<Channel> &channelList, User &user){
    std::string channel;
    
    if(iss >> channel){
        if(channel.at(0) == '#' || channel.at(0) == '&'){
            std::string key = "";
            iss >> key;
            std::list<Channel>::iterator it = getChannel(channelList, channel);
            if(it == channelList.end())
                createChannel(channel, key, channelList, user);
            else if(it != channelList.end() && !it->checkClient(user.getClientSocket())){
                if(it->getKeyExist() == true && it->getChannelMode("+k")){
                    if(key.empty() || key != it->getKey()){
                        messageSend(user.getClientSocket(), ERR_BADCHANNELKEY(channel));
                        return ;
                    }
                }
                if(it->getIsPublic() == false && it->getChannelMode("+i")){
                    if(!it->getInviteList(user.getClientSocket())){
                        messageSend(user.getClientSocket(), ERR_INVITEONLYCHAN(channel));
                        return ;
                    }
                    else
                        it->removeInviteList(user.getClientSocket());
                }
                it->addClientList(user.getClientSocket());
                messageSend(user.getClientSocket(), user.getIDENTITY() + " JOIN " + it->getName() + "\r\n");
                sendTopic(it, user);
            }
            else
                messageSend(user.getClientSocket(), ERR_USERONCHANNEL(it->getName(), user.getName(USER_NICK_NAME)));
        }else
            messageSend(user.getClientSocket(), ERR_INVALIDCHANNELNAME(channel));
    }else {
        std::string token = "JOIN";
        messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
    }
}

