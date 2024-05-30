#include "../../include/IRC.hpp"

void fillData(t_IRC_DATA *data, std::string passwordInput){
	data->yes = 1;
	data->fdMax = 0;
	data->nbytes = 0;
	data->serverSocket = 0;
	data->newClientSocket = 0;
	data->password = passwordInput;
	data->addrLen = sizeof(sockaddr_in);
	FD_ZERO(&data->readFds);
	FD_ZERO(&data->masterFds);
}
