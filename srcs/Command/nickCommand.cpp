#include "../../include/IRC.hpp"

static bool invalidNick(std::string input, int clientFd){
	if(input.find(':') != std::string::npos || input.find(' ') != std::string::npos || input.at(0) == '#' || isnumber(input.at(0))){
		std::string errorMsg = ERR_ERRONEUSNICKNAME(input);
		send(clientFd, errorMsg.c_str(), errorMsg.length(), 0);
		return true;
	}
	else
		return false;
}

static bool nickUnique(std::string input, int clientFD, std::map<int, User> &clientList){
	std::map<int, User>::iterator it = clientList.begin();
	while(it != clientList.end()){
		if(it->second.getName(USER_NICK_NAME) == input){
			std::string errorMSG = ERR_NICKNAMEINUSE(input) + ": Nickname is already in use.";
			if(clientFD == it->first){
				errorMSG = ERR_NICKNAMEINUSE(input) + ":This nickname is used by you.";
				send(clientFD, errorMSG.c_str(), errorMSG.length(), 0);
				return false;
			}
			send(clientFD, errorMSG.c_str(), errorMSG.length(), 0);
			return false;
		}
	}
	return true;
}

void commandNick(std::istringstream &iss, User &client, std::map<int, User> &clientList){
	std::string nick;
	if(iss >> nick){
		std::cout << "|" << nick << "|" << std::endl;
		if(invalidNick(nick, client.getClientSocket()))
			return ;
		if(nickUnique(nick, client.getClientSocket(), clientList))
			return ;
/* 		if(!client.getName(USER_NICK_NAME).empty()){ // eğer nick varsa ve değiştiriyorsa
			std::string changeMSG = client.getName(USER_NICK_NAME) + " "
		} */
		client.setName(USER_NICK_NAME, nick);
	}
}