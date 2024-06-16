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
                iss >> reason;
                ch->sendAllMsg(user.getIDENTITY() + " PART " + channel + " " +(reason.empty() ? "" : reason) + "\r\n");
                ch->removeClientList(user.getClientSocket());
                ch->printclientlist();
                if(ch->checkClientMode(user.getClientSocket())){
                    ch->removeModerator(user.getClientSocket());
                    ch->checkModerator(userList);
                }
            }else
                errMesageSend(user.getClientSocket(), ERR_NOTONCHANNEL(channel));
        }else
            errMesageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));
    }else
        errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
}


//chanlledaki remove dan sonra remove içinde mod check at. eğer çıkan kişi modsa ve başka mod kalmadıysa. clieentListdeki sonraki kişi mod olara
//atama işlemi yap.

//fatih'e nasıl channel siliniyor sor.