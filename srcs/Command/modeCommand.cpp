#include "../../include/IRC.hpp"

static void modeKey(const std::string key, const char &sign, const std::string &token,std::list<Channel>::iterator &ch, User &user){
	if(sign == '+'){
		if(key.empty()){
			messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS_MODE_VALUE(token));
			return ;
		}
		ch->setKeyExist(true);
		ch->setKey(key);
	}else{
		ch->setKeyExist(false);
		ch->setKey("");
	}
	ch->sendAllMsg(user.getIDENTITY() + "MODE " + ch->getName() + " " + sign + "k" + (key.empty() ? "" : (" " + key)) + "\r\n");
}

static void modeChannelOp(std::string &targetName, const char sign, const std::string &token, \
	std::map<int, User> &userList, std::list<Channel> &channelList, std::list<Channel>::iterator &ch, User &user){
	
	std::map<int, User>::iterator tgUser;
	if(targetName.empty()){
		messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS_MODE_VALUE(token));
		return ;
	}else
		tgUser = searchNick(targetName, userList);
	if(tgUser != userList.end()){
		if(sign == '+')
			ch->addModerator(tgUser->second.getClientSocket());
		else{
			ch->removeModerator(tgUser->second.getClientSocket());
			if(ch->getClientListSize() > 0)
				ch->ensureModeratorPresence(userList);
			else
				channelList.erase(ch); // Delete Channel.
		}
		ch->sendAllMsg(user.getIDENTITY() + "MODE " + ch->getName() + " " + sign + "o" + (targetName.empty() ? "" : (" " + targetName)) + "\r\n");
	}else
		messageSend(user.getClientSocket(), ERR_NOSUCHNICK(targetName));
}


void commandMode(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList){
	std::string target;
	std::string mode;
	std::string modeParemeters;
	const std::string token = "MODE";
	std::list<Channel>::iterator ch;
	std::map<int, User>::iterator targetUser;
	
	if(!(iss >> target))
		messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
	else
		ch = getChannel(channelList, target);
	if(ch == channelList.end())
		messageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(target));
	else if(!ch->checkClient(user.getClientSocket()))
		messageSend(user.getClientSocket(), ERR_NOTONCHANNEL(target));
	else{
		iss >> mode;
		if(!mode.empty() && mode != "b"){
			if(!ch->checkClientMode(user.getClientSocket()))
				messageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(target));
			else{
				iss >> modeParemeters;
				if(mode.at(1) == 'i'){
					ch->setIsPublic((mode == "+i") ? false : true);
					ch->sendAllMsg(user.getIDENTITY() + "MODE " + target + " " + mode + "\r\n");
				}
				else if(mode.at(1) == 'k')
					modeKey(modeParemeters, mode.at(0), token, ch, user);
				else if(mode.at(1) == 'o')
					modeChannelOp(modeParemeters, mode.at(0), token, userList, channelList, ch, user);
				if(mode.at(0) == '+' && mode.at(1) != 'o')
					ch->addChannelMode(mode);
				else if (mode.at(0) == '-'){
					mode[0] = '+';
					ch->removeChannelMode(mode);
				}
			}
		}else if(!ch->getJoinChannel(user.getClientSocket()) && mode != "b")
			ch->newJoinMsg(user, userList);
		else if(mode == "b" && !ch->getJoinChannel(user.getClientSocket())){
			ch->setJoinChannel(user.getClientSocket());
			messageSend(user.getClientSocket(), ":BAN LIST EMPTY!\r\n");
		}else{
			if(!ch->checkClientMode(user.getClientSocket()))
				messageSend(user.getClientSocket(), ERR_CHANOPRIVSNEEDED(target));
			else
				messageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS_MODE_VALUE(token));
		}
	}	
}