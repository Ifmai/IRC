#include "../../include/IRC.hpp"


bool portCheck(t_IRC_DATA *data, std::string port){
	for (size_t i = 0; i < port.size(); ++i) {
		if (!std::isdigit(port[i]))
			return false;
	}
	data->port = std::stoi(port);
	if(data->port > 65535 || data->port < 1024){
		std::cerr << "Port : beetween 1024 and 65535" << std::endl;
		return false;
	}
	return true;
}