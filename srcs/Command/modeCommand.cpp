#include "../../include/IRC.hpp"


void commandMode(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
	std::string target;
	std::string mode;
	std::string modeParemeters;
	std::string token = "MODE";
	std::string userInfo = IDENTIY_USER(user.getName(USER_NICK_NAME), user.getName(USER_NAME), user.getName(USER_HOST_INFO));

	if(iss >> target){
		std::list<Channel>::iterator ch = getChannel(channelList, target);
		if(ch != channelList.end()){
			if(ch->checkClient(user.getClientSocket()) && ch->checkClientMode(user.getClientSocket())){
				if(iss >> mode){
						if(mode.at(1) == 'i'){
							ch->setIsPublic((mode == "+i") ? false : true);
							ch->sendAllMsg(userInfo + "MODE " + target + " " + mode + "\r\n");
						}
						else if(mode.at(1) == 'k'){
							if(mode == "+k"){
								iss >> modeParemeters;
								ch->setKey(modeParemeters);
							}
							else{
								ch->setKey("");
							ch->sendAllMsg(userInfo + "MODE " + target + " " + mode + " " + (modeParemeters.empty() ? "" : modeParemeters) + "\r\n");
						}
						if(mode.at(0) == '+')
							ch->addChannelMode(mode);
						else if (mode.at(0) == '-')
							ch->removeChannelMode(mode);
				}else
					errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS_MODE_VALUE(token));
			}else{
				if(!ch->checkClient(user.getClientSocket()))
					errMesageSend(user.getClientSocket(), ERR_NOTONCHANNEL(target));
				else
					errMesageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(target));
			}
		}else
			errMesageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(target));
	}else
		errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
}