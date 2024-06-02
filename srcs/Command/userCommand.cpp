#include "../../include/IRC.hpp"

void commandUser(std::istringstream &iss, User &client){
	std::string usrName;
	std::string errMSG;
	std::string token = "USER";
	if(iss >> usrName){
		if(client.getName(USER_NAME).empty() && !client.getIsAuth()){
			client.setName(USER_NAME, usrName);
		}
		else{
			errMSG = ERR_ALREADYREGISTERED();
			send(client.getClientSocket(), errMSG.c_str(), errMSG.length(), 0);
		}
	}
	else{
		errMSG = ERR_NEEDMOREPARAMS(token);
		send(client.getClientSocket(), errMSG.c_str(), errMSG.length(), 0);
	}
}