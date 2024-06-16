#include "../../include/IRC.hpp"

static void onlyInviteChannel(std::list<Channel>::iterator &ch, User &user,  std::map<int, User>::iterator targetUser){
    if(ch->checkClientMode(user.getClientSocket())){
        messageSend(targetUser->second.getClientSocket(), \
            targetUser->second.getIDENTITY() + " INVITE " + targetUser->second.getName(USER_NICK_NAME) + " " + ch->getName() + "\r\n");
        
        messageSend(user.getClientSocket(), RPL_INVITING(user.getName(USER_NICK_NAME), ch->getName()));
        ch->addInviteList(targetUser->second.getClientSocket());
    }else
        messageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(ch->getName()));
}

static void defaultInviteChannel(std::list<Channel>::iterator &ch, User &user,  std::map<int, User>::iterator targetUser){
    messageSend(targetUser->second.getClientSocket(), \
        targetUser->second.getIDENTITY() + " INVITE " + targetUser->second.getName(USER_NICK_NAME) + " " + ch->getName() + "\r\n");
    
    messageSend(user.getClientSocket(),  RPL_INVITING(user.getName(USER_NICK_NAME), ch->getName()));
    ch->addInviteList(targetUser->second.getClientSocket());
}

void commandInvite(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
    std::string inviteUser;
    std::string channel;
    std::map<int, User>::iterator targetUser;
    std::list<Channel>::iterator ch;

    if(iss >> inviteUser){
        targetUser = searchNick(inviteUser, userList);
        if(targetUser != userList.end()){
            if(iss >> channel){
                ch = getChannel(channelList, channel);
                if(ch != channelList.end()){
                    if(!ch->checkClient(targetUser->second.getClientSocket())){
                        if(ch->checkClient(user.getClientSocket())){
                            if(ch->getChannelMode("+i"))
                                onlyInviteChannel(ch, user, targetUser);
                            else
                                defaultInviteChannel(ch, user, targetUser);
                        }else
                            messageSend(user.getClientSocket(), ERR_NOTONCHANNEL(channel));
                    }else
                        messageSend(user.getClientSocket(), ERR_USERONCHANNEL(inviteUser, channel));
                }else
                    messageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));
            }else
                messageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));
        }else
                messageSend(user.getClientSocket(), ERR_NOSUCHNICK(inviteUser));
    }else{
        std::string token = "LIST";
        messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
    }
}