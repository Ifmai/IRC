#include "../../include/IRC.hpp"

//user sınıfına uygun yazılacak vb. düzenleme ve ekleme yapılcak.
void newUserAdd(t_IRC_DATA *data){
	data->addrLen = sizeof(data->remoteAddr);
	if((data->newClientSocket = accept(data->serverSocket, (struct sockaddr *)&data->remoteAddr, &data->addrLen)) == -1)
		perror("accept");
	else{
		std::cout << "selam" << std::endl;
/* 		if(!passwordCheck(data)){
			close(data->newClientSocket);
			return ;
		} */
		FD_SET(data->newClientSocket, &data->masterFds); // ana listeye ekle
		if(data->newClientSocket > data->fdMax){
			data->fdMax = data->newClientSocket;
		}
		printf("selectserver: new connection from %s on "
			"socket %d\n", inet_ntoa(data->remoteAddr.sin_addr), data->newClientSocket);
	}
}