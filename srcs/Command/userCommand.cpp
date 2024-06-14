#include "../../include/IRC.hpp"

void commandUser(std::istringstream &iss, User &client){
	std::string usrName;
	std::string errMSG;
	std::string token = "USER";
	
	if(iss >> usrName){
		if(client.getName(USER_NAME).empty() && !client.getIsAuth()){
			client.setName(USER_NAME, usrName);
		}
		else
        	errMesageSend(client.getClientSocket(), ERR_ALREADYREGISTERED());
	}
	else
        errMesageSend(client.getClientSocket(), ERR_NEEDMOREPARAMS(token));
}