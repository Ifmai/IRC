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