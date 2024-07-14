#include "../../include/IRC.hpp"

void commandUser(std::istringstream &iss, User &client){
	std::string usrName;
	std::string realName;
	std::string errMSG;
	std::string token = "USER";
	
	if(iss >> usrName){
		if(client.getName(USER_NAME).empty() && !client.getIsAuth()){
			realName = fullMsg(iss);
			int spaceIndex = realName.find("0 * ");
			if(realName.find(" ") != std::string::npos){
				realName = realName.substr(spaceIndex + 1);
				client.setName(USER_NAME, usrName);
				client.setName(USER_REAL_NAME, realName);
			}else
				messageSend(client.getClientSocket(), "USER INPUT EXAMPLE : userName 0 * :Real Name\r\n");
		}
		else
        	messageSend(client.getClientSocket(), ERR_ALREADYREGISTERED());
	}
	else
        messageSend(client.getClientSocket(), ERR_NEEDMOREPARAMS(token));
}
