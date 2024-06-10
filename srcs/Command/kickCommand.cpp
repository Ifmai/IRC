#include "../../include/IRC.hpp"

void commandKick(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &clientList){
    std::string channel;
    std::string kickedUserName;
    std::string kickMessage;
    std::string errMsg;
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
                    }else{
                        errMsg = ERR_CHANOPRIVSNEEDED(channel);
                        send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
                    }
                }else{
                    errMsg = ERR_USERNOTINCHANNEL(kickedUserName, channel);
                    send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
                }
            }else{
                std::string token = "KICK";
                errMsg = ERR_NEEDMOREPARAMS_KICK_USER(token);
                send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
            }
        }else{
            errMsg = ERR_NOSUCHCHANNEL(channel);
            send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
        }
    }else{
        std::string token = "KICK";
        errMsg = ERR_NEEDMOREPARAMS(token);
        send(user.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
    }
}
