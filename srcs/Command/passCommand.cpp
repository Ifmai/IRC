#include "../../include/IRC.hpp"

void commandPass(std::istringstream &iss, User &client, std::map<int, User> &clientList, t_IRC_DATA *data){
	std::string pass;
	std::string errorMSG;
	if(iss >> pass && client.getPassword().empty()){
		std::cout << "|" << pass << "|" << std::endl;
		if(pass == data->password){
			client.setPassword(pass);
			std::cout << "Client |" << client.getPassword() << "|" << std::endl;
		}
		else{
			errorMSG = ERR_PASSWDMISMATCH();
			send(client.getClientSocket(), errorMSG.c_str(), errorMSG.length(), 0);
			handleClientQuit(data, client.getClientSocket(), clientList);
		}
	}
	else if (pass.empty()){
		std::string token = "PASS";
		errorMSG= ERR_NEEDMOREPARAMS(token);
		send(client.getClientSocket(),errorMSG.c_str(), errorMSG.length(), 0);
	}
	else if(!client.getPassword().empty()){
		errorMSG = ERR_ALREADYREGISTERED();
		send(client.getClientSocket(),errorMSG.c_str(), errorMSG.length(), 0);
	}
}