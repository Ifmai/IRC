#include "../../include/IRC.hpp"

static bool invalidNick(std::string input, int clientFd){
	if(input.find(':') != std::string::npos || input.find(' ') != std::string::npos || input.at(0) == '#' || isnumber(input.at(0))){
		errMesageSend(clientFd, ERR_ERRONEUSNICKNAME(input));
		return true;
	}
	else
		return false;
}

static bool nickUnique(std::string input, int clientFD, std::map<int, User> &clientList){
	std::map<int, User>::iterator it = clientList.begin();
	while(it != clientList.end()){
		if(it->second.getName(USER_NICK_NAME) == input){
			if(clientFD == it->first){
        		errMesageSend(clientFD, ERR_NICKNAMEINUSE(input) + " :This nickname is used by you.\r\n");
				return false;
			}
			errMesageSend(clientFD, ERR_NICKNAMEINUSE(input) + " : Nickname is already in use.\r\n");
			return false;
		}
		it++;
	}
	return true;
}

void commandNick(std::istringstream &iss, User &client, std::map<int, User> &clientList){
	std::string nick;

	if(iss >> nick){
		std::cout << "|" << nick << "|" << std::endl;
		if(invalidNick(nick, client.getClientSocket()))
			return ;
		if(!nickUnique(nick, client.getClientSocket(), clientList))
			return ;
		client.setName(USER_NICK_NAME, nick);
	}else{
		std::string token = "NICK";
        errMesageSend(client.getClientSocket(), ERR_NEEDMOREPARAMS(token));
	}
}