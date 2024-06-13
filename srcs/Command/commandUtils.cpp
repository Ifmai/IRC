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

void errMesageSend(int targetFd, std::string errMsg){
	send(targetFd, errMsg.c_str(), errMsg.length(), 0);
}

void sendAllUserMsg(std::map<int, User> &userList, std::string &msg){
	std::map<int, User>::iterator us = userList.begin();
	while(us != userList.end()){
		send(us->second.getClientSocket(), msg.c_str(), msg.length(), 0);
		us++;
	}
}