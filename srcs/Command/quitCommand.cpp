#include "../../include/IRC.hpp"

void commandQuit(std::istringstream &iss, User &user, std::list<Channel> &channelList, std::map<int, User> &userList, t_IRC_DATA *data){
    std::list<Channel>::iterator ch = channelList.begin();
    std::string reason = fullMsg(iss);
    std::string userInfo = user.getIDENTITY();
    std::string quitmsg = userInfo + " QUIT: " + (reason.empty() ? "" : reason) + "\r\n";
    
    while(ch != channelList.end()){
        if(ch->checkClient(user.getClientSocket())){
            ch->sendAllMsg(userInfo + " QUIT " + ch->getName() + " " + (reason.empty() ? "" : reason) + "\r\n");
            ch->removeClientList(user.getClientSocket());
            if(ch->checkClientMode(user.getClientSocket())){
                ch->removeModerator(user.getClientSocket());
                if(ch->getClientListSize() > 0)
                        ch->ensureModeratorPresence(userList);
                    else
                        channelList.erase(ch); // Delete Channel.
            }
        }
        ch++;
    }
    messageSend(user.getClientSocket(), quitmsg);
    close(user.getClientSocket());
    FD_CLR(user.getClientSocket(), &data->masterFds);
    userList.erase(userList.find(user.getClientSocket()));
}