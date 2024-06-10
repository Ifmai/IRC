#include "../../include/IRC.hpp"


static std::string fullMsg(std::istringstream &iss){
	std::string result = "";
	std::string msg;
	while(iss >> msg){
		if(result.empty())
			result += msg;
		else
			result += " " + msg;
	}
	return result;
}

// Notice and PrivMsg Command
void commandMSG(std::string &token, std::istringstream &iss, User &client, std::map<int, User> &clientList, std::list<Channel> channelList){
	std::string target;
	std::string msg;
	std::string errMsg;

	if(iss >> target){
		std::string userIdentity = IDENTIY_USER(client.getName(USER_NICK_NAME), client.getName(USER_NAME), client.getName(USER_HOST_INFO));
		std::string sendMsg = fullMsg(iss);
		msg = userIdentity + token + " " + target + " :" + sendMsg + "\r\n";
		if(target.at(0) == '#' || target.at(0) == '&'){ // Channel
			std::list<Channel>::iterator ch = getChannel(channelList, target);
			if(ch->checkClient(client.getClientSocket()))
				ch->sendMsgChannel(msg, client.getClientSocket());
			else{
				errMsg = ERR_CANNOTSENDTOCHAN(ch->getName());
				send(client.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
			}
		}
		else{ // User to User
			std::map<int, User>::iterator sendClient = searchNick(target, clientList);
			if(sendClient != clientList.end())
				send(sendClient->second.getClientSocket(), msg.c_str(), msg.length(), 0);
			else if (token == "PRIVMSG"){
				errMsg = ERR_NOSUCHNICK(client.getName(USER_NICK_NAME), target);
				send(client.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
			}
		}
	}
	else if (token == "PRIVMSG"){
		errMsg = ERR_NEEDMOREPARAMS(token);
		send(client.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
	}
}