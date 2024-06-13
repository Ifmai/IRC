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