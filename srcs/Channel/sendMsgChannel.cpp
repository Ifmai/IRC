#include "../../include/Channel.hpp"

void Channel::sendMsgChannel(std::string msg, int senderFd){
	std::list<int>::iterator sender = this->clientList.begin();
	while(sender != this->clientList.end()){
		if(*sender != senderFd)
			messageSend(*sender, msg);
		sender++;
	}
}

void Channel::sendAllMsg(std::string msg){
	std::list<int>::iterator sender = this->clientList.begin();
	while(sender != this->clientList.end()){
			messageSend(*sender, msg);
		sender++;
	}
}

void Channel::newJoinMsg(User &user, std::map<int, User> userList){
	std::string userInfo;
	std::string mode;

	std::list<int>::iterator sender = this->clientList.begin();
	std::map<int, User>::iterator client;
	std::list<std::string>::iterator channelModes = this->channelMode.begin();

	while(sender != this->clientList.end()){
		if(user.getClientSocket() != *sender){
			channelModes = this->channelMode.begin();
			client = userList.find(*sender);
			userInfo = client->second.getIDENTITY(); 
			messageSend(user.getClientSocket(), userInfo + " JOIN " + this->channelName + "\r\n");
			messageSend(*sender, user.getIDENTITY() + " JOIN " + this->channelName + "\r\n");
			if(this->checkClientMode(client->second.getClientSocket())){
				messageSend(user.getClientSocket(), userInfo + " MODE " + this->channelName + " +o " + client->second.getName(USER_NICK_NAME) + "\r\n");
			}
		}
		sender++;
	}
	while(channelModes != this->channelMode.end()){
		mode = *channelModes;
		if(mode == "+k")
			messageSend(user.getClientSocket()," MODE " + this->channelName + " " + mode + " " + this->channelKey + "\r\n");
		else
			messageSend(user.getClientSocket(), " MODE " + this->channelName + " " + mode + "\r\n");
		channelModes++;
	}
}

void Channel::writeClientList(int sendFd, std::map<int, User> &userList){
    std::list<int>::iterator it = this->clientList.begin();
    std::map<int, User>::iterator user;
    std::string sendMsg;

    while(it != this->clientList.end()){
        user = userList.find(*it);
		if(it != this->clientList.end())
        	sendMsg += "User Nick: " + user->second.getName(USER_NICK_NAME) + "\n";
		else
        	sendMsg += "User Nick: " + user->second.getName(USER_NICK_NAME);
    }
	sendMsg += "\r\n";
    messageSend(sendFd, sendMsg);
}