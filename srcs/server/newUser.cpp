#include "../../include/IRC.hpp"

static bool passwordCheck(t_IRC_DATA *data){
	if((data->nbytes = recv(data->newClientSocket, data->buff, sizeof(data->buff), 0)) < 0){
		std::cerr << "Error reading from client." << std::endl;
		perror("recv");
		return false;
	}
	data->buff[data->nbytes - 1] = '\0';
	std::cout << data->buff << std::endl;
	std::cout << data->password << std::endl;
	if(strcmp(data->buff, data->password.c_str()) == 0){
		std::string success_message = "Password correct. Welcome!";
        if(send(data->newClientSocket, success_message.c_str(), success_message.size(), 0) == -1)
			perror("send");
		return true;
	}
	else{
		std::string failure_message = "Incorrect password. Connection closed.";
        if(send(data->newClientSocket, failure_message.c_str(), failure_message.size(), 0) == -1)
			perror("send");
		return false;
	}
}

//user sınıfına uygun yazılacak vb. düzenleme ve ekleme yapılcak.
void newUserAdd(t_IRC_DATA *data){
	data->addrLen = sizeof(data->remoteAddr);
	if((data->newClientSocket = accept(data->serverSocket, (struct sockaddr *)&data->remoteAddr, &data->addrLen)) == -1)
		perror("accept");
	else{
		std::cout << "selam" << std::endl;
		if(!passwordCheck(data)){
			close(data->newClientSocket);
			return ;
		}
		FD_SET(data->newClientSocket, &data->masterFds); // ana listeye ekle
		if(data->newClientSocket > data->fdMax){
			data->fdMax = data->newClientSocket;
		}
		printf("selectserver: new connection from %s on "
			"socket %d\n", inet_ntoa(data->remoteAddr.sin_addr), data->newClientSocket);
	}
}