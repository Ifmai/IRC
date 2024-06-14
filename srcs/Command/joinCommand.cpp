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
    joinMsg = userIdentity + " JOIN " + channelName + "\r\n";
    send(user.getClientSocket(), joinMsg.c_str(), joinMsg.length(), 0);
    modeMsg = "MODE " + channelName +  " +o " + user.getName(USER_NICK_NAME) + "\r\n";
    if(!key.empty()){
        it->setKeyExist(true);
        it->setKey(key);
        it->addChannelMode("+k");
    }
    send(user.getClientSocket(), modeMsg.c_str(), modeMsg.length(), 0);
    if(!key.empty()){
        modeMsg = userIdentity + " MODE " + channelName +  " +k " + key + "\r\n";
        send(user.getClientSocket(), modeMsg.c_str(), modeMsg.length(), 0);
    }
}

void commandJoin(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
    std::string channel;
    std::string joinMsg;
    
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
                        errMesageSend(user.getClientSocket(), ERR_BADCHANNELKEY(channel));
                        return ;
                    }
                }
                if(it->getIsPublic() == false && it->getChannelMode("+i")){
                    if(!it->getInviteList(user.getClientSocket())){
                        errMesageSend(user.getClientSocket(), ERR_INVITEONLYCHAN(channel));
                        return ;
                    }
                }
                joinMsg = user.getIDENTITY() + " JOIN " + it->getName() + "\r\n";                 
                it->addClientList(user.getClientSocket());
                send(user.getClientSocket(), joinMsg.c_str(), joinMsg.length(), 0);
                std::string topic = it->getTopic();
                if(!topic.empty()){
                    std::string msgTopic = RPL_TOPIC(it->getChangerTopic(), channel, topic);
                    send(user.getClientSocket(), msgTopic.c_str(), msgTopic.length(), 0);
                }else{
                    std::string msgTopic = RPL_NOTOPIC(channel);
                    send(user.getClientSocket(), msgTopic.c_str(), msgTopic.length(), 0);
                }
                it->newJoinMsg(user, userList);//join olan kişi için channeldaki kişilerin mod ve kimler olduğuna dair mesaj gidicek
            }
            else
                errMesageSend(user.getClientSocket(), ERR_USERONCHANNEL(it->getName(), user.getName(USER_NICK_NAME)));
        }else
            errMesageSend(user.getClientSocket(), ERR_INVALIDCHANNELNAME(channel));
    }else {
        std::string token = "JOIN";
        errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
    }
}

