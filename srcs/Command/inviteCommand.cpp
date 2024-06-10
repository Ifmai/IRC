#include "../../include/IRC.hpp"

void onlyInviteChannel(std::list<Channel>::iterator &ch, User &user, std::map<int, User> &userList,  std::map<int, User>::iterator targetUser){
    std::string sendMsg;
    std::string userInfo;
    std::string errMsg;
    if(ch->checkClientMode(user.getClientSocket())){
        userInfo = IDENTIY_USER(targetUser->second.getName(USER_NICK_NAME), targetUser->second.getName(USER_NAME), targetUser->second.getName(USER_HOST_INFO));
        sendMsg = userInfo + " INVITE " + targetUser->second.getName(USER_NICK_NAME) + " " + ch->getName();
        send(targetUser->second.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
        sendMsg = RPL_INVITING(user.getName(USER_NICK_NAME), ch->getName());
        send(user.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
        ch->addInviteList(targetUser->second.getClientSocket());
    }else{
        errMsg = ERR_CHANOPRIVSNEEDED(ch->getName());
        send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
    }
}

void defaultInviteChannel(std::list<Channel>::iterator &ch, User &user, std::map<int, User> &userList,  std::map<int, User>::iterator targetUser){
    std::string sendMsg;
    std::string userInfo;
    std::string errMsg;

    userInfo = IDENTIY_USER(targetUser->second.getName(USER_NICK_NAME), targetUser->second.getName(USER_NAME), targetUser->second.getName(USER_HOST_INFO));
    sendMsg = userInfo + " INVITE " + targetUser->second.getName(USER_NICK_NAME) + " " + ch->getName();
    send(targetUser->second.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
    sendMsg = RPL_INVITING(user.getName(USER_NICK_NAME), ch->getName());
    send(user.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
    ch->addInviteList(targetUser->second.getClientSocket());
}

void commandInvite(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
    std::string inviteUser;
    std::string channel;
    std::string errMsg;
    if(iss >> inviteUser){
        std::map<int, User>::iterator targetUser = searchNick(inviteUser, userList);
        if(targetUser != userList.end()){
            if(iss >> channel){
                std::list<Channel>::iterator ch = getChannel(channelList, channel);
                if(ch != channelList.end()){
                    if(!ch->checkClient(targetUser->second.getClientSocket())){
                        if(ch->checkClient(user.getClientSocket())){
                            if(ch->getChannelMode("+i"))
                                onlyInviteChannel(ch, user, userList, targetUser);
                            else
                                defaultInviteChannel(ch, user, userList, targetUser);
                        }else{
                            errMsg = ERR_NOTONCHANNEL(channel);
                            send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
                        }
                    }else{
                        errMsg = ERR_USERONCHANNEL(inviteUser, channel);
                        send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
                    }
                }else{
                    errMsg = ERR_NOSUCHCHANNEL(channel);
                    send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
                }
            }else{
                errMsg = ERR_NOSUCHCHANNEL(channel);
                send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
            }
        }else{
            errMsg =  ERR_NOSUCHNICK(inviteUser);
            send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
        }
    }else{
        std::string token = "LIST";
        errMsg = ERR_NEEDMOREPARAMS(token);
        send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
    }
}