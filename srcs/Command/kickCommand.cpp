#include "../../include/IRC.hpp"

void commandKick(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &clientList){
    std::string channel;
    std::string kickedUserName;
    std::string kickMessage;
    std::string userIdentity = IDENTIY_USER(user.getName(USER_NICK_NAME), user.getName(USER_NAME), user.getName(USER_HOST_INFO));

    std::map<int, User>::iterator kickedUser;
    if(iss >> channel){
        std::list<Channel>::iterator ch = getChannel(channelList, channel);
        if(ch != channelList.end()){
            if(iss >> kickedUserName){
                kickedUser = searchNick(kickedUserName, clientList);
                if(ch->checkClient(kickedUser->second.getClientSocket()) && ch->checkClient(user.getClientSocket())){
                    if(ch->checkClientMode(user.getClientSocket())){
                        kickMessage = fullMsg(iss);
                        if(kickMessage.empty())
                            kickMessage = DEFAULT_KICK_MSG(channel, user.getName(USER_NICK_NAME));
                        else
                            kickedUserName = " .Kicked By. " + user.getName(USER_NICK_NAME) + "\r\n";
                        std::string allmsg = userIdentity+ " KICK " + channel + " " + kickedUserName + "\r\n";
                        send(kickedUser->second.getClientSocket(), kickMessage.c_str(), kickMessage.length(), 0);
                        ch->sendAllMsg(allmsg);
                        ch->removeClientList(kickedUser->second.getClientSocket());
                    }else
                        errMesageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(channel));
                }else{
                    if(!ch->checkClient(user.getClientSocket()))
                        errMesageSend(user.getClientSocket(), ERR_USERNOTINCHANNEL(user.getName(USER_NICK_NAME), channel));
                    else
                        errMesageSend(user.getClientSocket(), ERR_USERNOTINCHANNEL(kickedUserName, channel));
                }
            }else{
                std::string token = "KICK";
                errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
            }
        }else
            errMesageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));
    }else{
        std::string token = "KICK";
        errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
    }
}
