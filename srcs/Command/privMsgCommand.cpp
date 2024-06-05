#include "../../include/IRC.hpp"

void commandPRIVMSG(std::istringstream &iss, std::string buff, User &client, std::map<int, User> &clientList){
	std::string target;
	std::string msg;
	std::string errMsg;

	if(iss >> target){
		std::cout << "host : " << client.getName(USER_HOST_INFO) << std::endl;
		std::string userIdentity =  ":" + client.getName(USER_NICK_NAME) + "!" + client.getName(USER_NAME) + "@" + client.getName(USER_HOST_INFO) + " ";
		if(target.at(0) == '#'){ // Channel
			//channelist if
			//else 404 Do not send messages to the channel.
		}
		else{ // User to User
			User* sendClient = searchNick(target, clientList);
			if(sendClient != nullptr){
				msg = userIdentity + buff + "\r\n";
				std::cout << msg << std::endl;
				send(sendClient->getClientSocket(), msg.c_str(), msg.length(), 0);
			}
			else{
				errMsg = ERR_NOSUCHNICK(client.getName(USER_NICK_NAME), target);
				send(client.getClientSocket(), errMsg.c_str(), errMsg.length(), 0);
			}
		}
	}
}