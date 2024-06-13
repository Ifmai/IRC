#include "../../include/IRC.hpp"

void onlyInviteChannel(std::list<Channel>::iterator &ch, User &user,  std::map<int, User>::iterator targetUser){
    std::string sendMsg;
    std::string userInfo;
    if(ch->checkClientMode(user.getClientSocket())){
        userInfo = IDENTIY_USER(targetUser->second.getName(USER_NICK_NAME), targetUser->second.getName(USER_NAME), targetUser->second.getName(USER_HOST_INFO));
        sendMsg = userInfo + " INVITE " + targetUser->second.getName(USER_NICK_NAME) + " " + ch->getName() + "\r\n";
        send(targetUser->second.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
        sendMsg = RPL_INVITING(user.getName(USER_NICK_NAME), ch->getName());
        send(user.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
        ch->addInviteList(targetUser->second.getClientSocket());
    }else
        errMesageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(ch->getName()));
    ch->printInviteList();
}

void defaultInviteChannel(std::list<Channel>::iterator &ch, User &user,  std::map<int, User>::iterator targetUser){
    std::string sendMsg;
    std::string userInfo;

    userInfo = IDENTIY_USER(targetUser->second.getName(USER_NICK_NAME), targetUser->second.getName(USER_NAME), targetUser->second.getName(USER_HOST_INFO));
    sendMsg = userInfo + " INVITE " + targetUser->second.getName(USER_NICK_NAME) + " " + ch->getName();
    send(targetUser->second.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
    sendMsg = RPL_INVITING(user.getName(USER_NICK_NAME), ch->getName());
    send(user.getClientSocket(), sendMsg.c_str(), sendMsg.length(), 0);
    ch->addInviteList(targetUser->second.getClientSocket());
    ch->printInviteList();
}

void commandInvite(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
    std::string inviteUser;
    std::string channel;
    if(iss >> inviteUser){
        std::map<int, User>::iterator targetUser = searchNick(inviteUser, userList);
        if(targetUser != userList.end()){
            if(iss >> channel){
                std::list<Channel>::iterator ch = getChannel(channelList, channel);
                if(ch != channelList.end()){
                    if(!ch->checkClient(targetUser->second.getClientSocket())){
                        if(ch->checkClient(user.getClientSocket())){
                            if(ch->getChannelMode("+i"))
                                onlyInviteChannel(ch, user, targetUser);
                            else
                                defaultInviteChannel(ch, user, targetUser);
                        }else
                            errMesageSend(user.getClientSocket(), ERR_NOTONCHANNEL(channel));
                    }else
                        errMesageSend(user.getClientSocket(), ERR_USERONCHANNEL(inviteUser, channel));
                }else
                    errMesageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));
            }else
                errMesageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));
        }else
                errMesageSend(user.getClientSocket(), ERR_NOSUCHNICK(inviteUser));
    }else{
        std::string token = "LIST";
        errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
    }
}