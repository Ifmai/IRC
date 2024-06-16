#include "../../include/IRC.hpp"

std::string fullMsg(std::istringstream &iss){
	std::string result = "";
	std::string msg;
	while(iss >> msg){
		if(result.empty())
			result += msg;
		else
			result += " " + msg;
	}
	return result;
}

void messageSend(int targetFd, std::string msg){
	if(send(targetFd, msg.c_str(), msg.length(), 0) == -1)
		perror("send");
}

void sendAllUserMsg(std::map<int, User> &userList, std::string &msg){
	std::map<int, User>::iterator us = userList.begin();
	while(us != userList.end()){
		send(us->second.getClientSocket(), msg.c_str(), msg.length(), 0);
		us++;
	}
}