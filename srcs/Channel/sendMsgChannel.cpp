#include "../../include/Channel.hpp"

void Channel::sendMsgChannel(std::string msg, int senderFd){
	std::list<int>::iterator sender = this->clientList.begin();
	while(sender != this->clientList.end()){
		if(*sender != senderFd)
			send(*sender, msg.c_str(), msg.length(), 0);
		sender++;
	}
}

void Channel::sendAllMsg(std::string msg){
	std::list<int>::iterator sender = this->clientList.begin();
	while(sender != this->clientList.end()){
			send(*sender, msg.c_str(), msg.length(), 0);
		sender++;
	}
}

void Channel::newJoinMsg(User &user, std::map<int, User> userList){
	std::string userInfo;
	std::string msgJOIN;
	std::string msgMODE;
	std::string mode;

	std::list<int>::iterator sender = this->clientList.begin();
	std::map<int, User>::iterator client;
	std::list<std::string>::iterator channelModes = this->channelMode.begin();

	while(sender != this->clientList.end()){
		if(user.getClientSocket() != *sender){
			channelModes = this->channelMode.begin();
			client = userList.find(*sender);
			userInfo = client->second.getIDENTITY(); 
			msgJOIN = userInfo + " JOIN " + this->channelName + "\r\n";
			send(user.getClientSocket(), msgJOIN.c_str(), msgJOIN.length(), 0);
			msgJOIN = user.getIDENTITY() + " JOIN " + this->channelName + "\r\n";
			send(*sender, msgJOIN.c_str(), msgJOIN.length(), 0);
			if(this->checkClientMode(client->second.getClientSocket())){
				msgMODE = userInfo + " MODE " + this->channelName + " +o " + client->second.getName(USER_NICK_NAME) + "\r\n";
				send(user.getClientSocket(), msgMODE.c_str(), msgMODE.length(), 0);
			}
			while(channelModes != this->channelMode.end()){
				mode = *channelModes;
				if(mode == "+k")
					msgMODE = userInfo + " MODE " + this->channelName + " " + mode + " " + this->channelKey + "\r\n";
				else
					msgMODE = userInfo + " MODE " + this->channelName + " " + mode + "\r\n";
				send(user.getClientSocket(), msgMODE.c_str(), msgMODE.length(), 0);
				channelModes++;
			}
		}
		sender++;
	}
}

void Channel::writeClientList(int sendFd, std::map<int, User> &userList){
    std::list<int>::iterator it = this->clientList.begin();
    std::map<int, User>::iterator user;
    std::string sendMsg;

    while(it != this->clientList.end()){
        user = userList.find(*it);
        it++;
		if(it != this->clientList.end())
        	sendMsg += "User Nick: " + user->second.getName(USER_NICK_NAME) + "\n";
		else
        	sendMsg += "User Nick: " + user->second.getName(USER_NICK_NAME);
    }
	sendMsg += "\r\n";
    send(sendFd, sendMsg.c_str(), sendMsg.length(), 0);
}