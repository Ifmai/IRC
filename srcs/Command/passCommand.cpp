#include "../../include/IRC.hpp"

void commandPass(std::istringstream &iss, User &client, std::map<int, User> &clientList, t_IRC_DATA *data){
	std::string pass;
	if(iss >> pass && client.getPassword().empty()){
		if(pass.at(0) == ':')
			pass.erase(0, 1);
 		if(pass == data->password)
			client.setPassword(pass);
		else{
        	messageSend(client.getClientSocket(), ERR_PASSWDMISMATCH());
			handleClientQuit(data, client.getClientSocket(), clientList);
		}
	}
	else if (pass.empty() && !client.getIsAuth()){
		std::string token = "PASS";
        messageSend(client.getClientSocket(), ERR_NEEDMOREPARAMS(token));
	}
	else if(!client.getPassword().empty())
        messageSend(client.getClientSocket(), ERR_ALREADYREGISTERED());
}