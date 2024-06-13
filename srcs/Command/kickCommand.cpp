#include "../../include/IRC.hpp"

void commandKick(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &clientList){
    std::string channel;
    std::string kickedUserName;
    std::string kickMessage;
    std::map<int, User>::iterator kickedUser;
    if(iss >> channel){
        std::list<Channel>::iterator ch = getChannel(channelList, channel);
        if(ch != channelList.end()){
            if(iss >> kickedUserName){
                kickedUser = searchNick(kickedUserName, clientList);
                if(ch->checkClient(kickedUser->second.getClientSocket())){
                    if(ch->checkClientMode(kickedUser->second.getClientSocket())){
                        kickMessage = fullMsg(iss);
                        if(kickMessage.empty())
                            kickMessage = DEFAULT_KICK_MSG(channel, user.getName(USER_NICK_NAME));
                        else
                            kickedUserName = " .Kicked By." + kickedUser->second.getName(USER_NICK_NAME) + "\r\n";
                        send(kickedUser->second.getClientSocket(), kickMessage.c_str(), kickMessage.length(), 0);
                        ch->removeClientList(kickedUser->second.getClientSocket());
                        std::string allmsg = "KICK " + channel + " " + kickedUserName + "\r\n";
                        ch->sendAllMsg(allmsg);
                    }else
                        errMesageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(channel));
                }else
                    errMesageSend(user.getClientSocket(), ERR_USERNOTINCHANNEL(kickedUserName, channel));
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
