#include "../../include/IRC.hpp"


void commandPart(std::istringstream &iss, User &user, std::list<Channel> &channelList, std::map<int, User> &userList){
    std::list<Channel>::iterator ch;
    std::string channel;
    std::string reason;
    std::string token = "PART";

    if(iss >> channel){
        ch = getChannel(channelList, channel);
        if(ch != channelList.end()){
            if(ch->checkClient(user.getClientSocket())){
                reason = fullMsg(iss);
                ch->sendAllMsg(user.getIDENTITY() + " PART " + channel + " " +(reason.empty() ? "" : reason) + "\r\n");
                ch->removeClientList(user.getClientSocket());
                if(ch->checkClientMode(user.getClientSocket())){
                    ch->removeModerator(user.getClientSocket());
                    if(ch->getClientListSize() > 0)
                        ch->ensureModeratorPresence(userList);
                    else
                        channelList.erase(ch); // Delete Channel.
                }
            }else
                messageSend(user.getClientSocket(), ERR_NOTONCHANNEL(channel));
        }else
            messageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));
    }else
        messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
}
