#include "../../include/IRC.hpp"

static void createChannel(std::string buff, std::string channelName, std::string key, std::list<Channel> &channelList, User &user){
    std::string joinMsg;
    std::string modeMsg;
    std::string userIdentity = IDENTIY_USER(user.getName(USER_NICK_NAME), user.getName(USER_NAME), user.getName(USER_HOST_INFO));
    if(channelName.at(0) == '#')
        channelList.push_back(Channel(channelName, "#", user.getClientSocket()));
    else if(channelName.at(0) == '&')
        channelList.push_back(Channel(channelName, "&", user.getClientSocket()));
    std::list<Channel>::iterator it = getChannel(channelList, channelName);
    it->addModerator(user.getClientSocket());
    joinMsg = userIdentity + buff + "\r\n";
    modeMsg = "MODE " + channelName +  " +o " + user.getName(USER_NICK_NAME) + "\r\n";
    if(!key.empty()){
        it->setKeyExist(true);
        it->setKey(key);
        it->addChannelMode("+k");
    }
    send(user.getClientSocket(), joinMsg.c_str(), joinMsg.length(), 0);
    send(user.getClientSocket(), modeMsg.c_str(), modeMsg.length(), 0);
    if(!key.empty()){
        modeMsg = "MODE " + channelName +  " +k " + key + "\r\n";
        send(user.getClientSocket(), modeMsg.c_str(), modeMsg.length(), 0);
    }
}

void commandJoin(std::string buff, std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
    std::string channel;
    std::string errorMsg;
    std::string joinMsg;
    std::string userIdentity = IDENTIY_USER(user.getName(USER_NICK_NAME), user.getName(USER_NAME), user.getName(USER_HOST_INFO));
    
    if(iss >> channel){
        if(channel.at(0) == '#' || channel.at(0) == '&'){
            std::string key = "";
            iss >> key;
            std::list<Channel>::iterator it = getChannel(channelList, channel);
            if(it == channelList.end())
                createChannel(buff, channel, key, channelList, user);
            else if(it != channelList.end() && !it->checkClient(user.getClientSocket())){
                if(it->getKeyExist() == true && it->getChannelMode("+k")){
                    if(key.empty() || key != it->getKey()){
                        errorMsg = ERR_BADCHANNELKEY(channel);
                        send(user.getClientSocket(), errorMsg.c_str(), errorMsg.length(), 0); 
                    }
                }
                if(it->getIsPublic() == true && it->getChannelMode("+i")){
                    if(!it->getInviteList(user.getClientSocket())){
                        errorMsg = ERR_INVITEONLYCHAN(channel);
                        send(user.getClientSocket(), errorMsg.c_str(), errorMsg.length(), 0);
                    }
                }
                joinMsg = userIdentity + buff + "\r\n";
                send(user.getClientSocket(), joinMsg.c_str(), joinMsg.length(), 0);
                //topic mesaj
                it->newJoinMsg(user.getClientSocket(), userList);//join olan kişi için channeldaki kişilerin mod ve kimler olduğuna dair mesaj gidicek
                //channeldaki herkese katılan kişinin bilgisi gidicek. bundan emin değilim bakıcam.
            }
            else{
                errorMsg = ERR_USERONCHANNEL(it->getName(), user.getName(USER_NICK_NAME));
                send(user.getClientSocket(), errorMsg.c_str(), errorMsg.length(), 0);
            }
        }else{
            errorMsg = ERR_INVALIDCHANNELNAME(channel);
            send(user.getClientSocket(), errorMsg.c_str(), errorMsg.length(), 0);
        }
    }else {
        std::string token = "JOIN";
        errorMsg = ERR_NEEDMOREPARAMS(token);
        send(user.getClientSocket(), errorMsg.c_str(), errorMsg.length(), 0);
    }
}

