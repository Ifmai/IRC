#include "../../include/IRC.hpp"

void commandPass(std::istringstream &iss, User &client, std::map<int, User> &clientList, t_IRC_DATA *data){
	std::string pass;
	if(iss >> pass && client.getPassword().empty()){
		std::cout << "|" << pass << "|" << std::endl;
		if(pass == data->password){
			client.setPassword(pass);
			std::cout << "Client |" << client.getPassword() << "|" << std::endl;
		}
		else{
        	errMesageSend(client.getClientSocket(), ERR_PASSWDMISMATCH());
			handleClientQuit(data, client.getClientSocket(), clientList);
		}
	}
	else if (pass.empty() && !client.getIsAuth()){
		std::string token = "PASS";
        errMesageSend(client.getClientSocket(), ERR_NEEDMOREPARAMS(token));
	}
	else if(!client.getPassword().empty())
        errMesageSend(client.getClientSocket(), ERR_ALREADYREGISTERED());
}