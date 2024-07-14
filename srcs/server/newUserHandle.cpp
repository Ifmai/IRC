#include "../../include/IRC.hpp"

void newUserAdd(t_IRC_DATA *data, std::map<int, User> &clientList){
	data->addrLen = sizeof(data->remoteAddr);
	if((data->newClientSocket = accept(data->serverSocket, (struct sockaddr *)&data->remoteAddr, &data->addrLen)) == -1)
		perror("accept");
	else{
		FD_SET(data->newClientSocket, &data->masterFds); // ana listeye ekle
		clientList.insert(std::pair<int, User>(data->newClientSocket, User(data->newClientSocket)));//map'ekleme
		if(data->newClientSocket > data->fdMax){
			data->fdMax = data->newClientSocket;
		}
		std::cout << "selectserver: new connection from " << inet_ntoa(data->remoteAddr.sin_addr) << " on socket " << data->newClientSocket << std::endl;
	}
}