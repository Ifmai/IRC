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
void commandMSG(std::string &token, std::istringstream &iss, User &client, std::map<int, User> &clientList){
	std::string target;
	std::string msg;
	std::string errMsg;

	if(iss >> target){
		//std::cout << "host : " << client.getName(USER_HOST_INFO) << std::endl;
		std::string userIdentity = IDENTIY_USER(client.getName(USER_NICK_NAME), client.getName(USER_NAME), client.getName(USER_HOST_INFO));
		if(target.at(0) == '#'){ // Channel
			//channelist if
			//else 404 Do not send messages to the channel.
		}
		else{ // User to User
			User* sendClient = searchNick(target, clientList);
			if(sendClient != nullptr ){
				std::string sendMsg = fullMsg(iss);
				msg = userIdentity + token + " " + target + " :" + sendMsg + "\r\n";
				std::cout << msg << std::endl;
				send(sendClient->getClientSocket(), msg.c_str(), msg.length(), 0);
			}
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