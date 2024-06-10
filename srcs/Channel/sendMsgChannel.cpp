#include "../../include/Channel.hpp"

void Channel::sendMsgChannel(std::string msg, int senderFd){
	std::list<int>::iterator sender = this->clientList.begin();
	while(sender != this->clientList.end()){
		if(*sender != senderFd)
			send(*sender, msg.c_str(), msg.length(), 0);
		sender++;
	}
}

void Channel::sendChangeTopicMsg(std::string msg){
	std::list<int>::iterator sender = this->clientList.begin();
	while(sender != this->clientList.end()){
			send(*sender, msg.c_str(), msg.length(), 0);
		sender++;
	}
}

void Channel::newJoinMsg(int userFd, std::map<int, User> userList){
	std::string userInfo;
	std::string msgJOIN;
	std::string msgMODE;
	std::list<int>::iterator sender = this->clientList.end();
	std::map<int, User>::iterator client;
	while(sender != this->clientList.end()){
		client = userList.find(*sender);
		userInfo = IDENTIY_USER(client->second.getName(USER_NICK_NAME), client->second.getName(USER_NAME), client->second.getName(USER_HOST_INFO));
		msgJOIN = userInfo + " JOIN " + this->channelName + "\r\n";
		send(userFd, msgJOIN.c_str(), msgJOIN.length(), 0);
		if(this->checkClientMode(client->second.getClientSocket())){
			msgMODE = "MODE " + this->channelName + " +o " + client->second.getName(USER_NICK_NAME) + "\r\n";
			send(userFd, msgMODE.c_str(), msgMODE.length(), 0);
		}
		sender++;
	}
}

/* for (size_t j = 0; j < server->getChannels()[i].clients.size() - 1; j++)
{
	sender(client->client_fd, Prefix(server->getChannels()[i].clients[j]) + " JOIN " + channel + "\r\n");
	if (server->getChannels()[i].clients[j].isOperator)
	{
		sender(client->client_fd, "MODE " + channel + " +o " + server->getChannels()[i].clients[j].nickname + "\r\n");
	}
} */