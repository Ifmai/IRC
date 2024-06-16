#include "../../include/IRC.hpp"


void commandMode(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
	std::string target;
	std::string mode;
	std::string modeParemeters;
	std::string token = "MODE";
	std::string userInfo = user.getIDENTITY();
	std::list<Channel>::iterator ch;
	std::map<int, User>::iterator targetUser;
	
	if(iss >> target){
		if(target.at(0) == '#'){
			ch = getChannel(channelList, target);
			if(ch != channelList.end()){
				if(ch->checkClient(user.getClientSocket()) && ch->checkClientMode(user.getClientSocket())){
					if(iss >> mode){
							if(mode.at(0) == 'b'){
								return ;
							}
							if(mode.at(1) == 'i'){
								ch->setIsPublic((mode == "+i") ? false : true);
								ch->sendAllMsg(userInfo + "MODE " + target + " " + mode + "\r\n");
							}
							else if(mode.at(1) == 'k'){
								if(mode == "+k"){
									iss >> modeParemeters;
									if(modeParemeters.empty()){
										messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS_MODE_VALUE(token));
										return ;
									}
									ch->setKeyExist(true);
									ch->setKey(modeParemeters);
								}
								else{
									ch->setKeyExist(false);
									ch->setKey("");
								}
								ch->sendAllMsg(userInfo + "MODE " + target + " " + mode + (modeParemeters.empty() ? "" : (" " + modeParemeters)) + "\r\n");
							}
							else if(mode.at(1) == 'o'){
								iss >> modeParemeters;
								if(modeParemeters.empty()){
									messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS_MODE_VALUE(token));
									return ;
								}
								else
									targetUser = searchNick(modeParemeters, userList);
								if(mode == "+o")
									ch->addModerator(targetUser->second.getClientSocket());
								else{
									ch->removeModerator(targetUser->second.getClientSocket());
									ch->ensureModeratorPresence(userList);
								}
								ch->sendAllMsg(userInfo + "MODE " + target + " " + mode + (modeParemeters.empty() ? "" : (" " + modeParemeters)) + "\r\n");
							}
							if(mode.at(0) == '+' && mode.at(1) != 'o')
								ch->addChannelMode(mode);
							else if (mode.at(0) == '-'){
								mode[0] = '+';
								ch->removeChannelMode(mode);
								if(ch->getClientListSize() > 0)
									ch->ensureModeratorPresence(userList);
								else
									channelList.erase(ch); // Delete Channel.
							}
					}else
						messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS_MODE_VALUE(token));
				}else{
					if(!ch->checkClient(user.getClientSocket()))
						messageSend(user.getClientSocket(), ERR_NOTONCHANNEL(target));
					else
						messageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(target));
				}
			}else
				messageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(target));
		}
	}else
		messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
}