#include "../../include/IRC.hpp"

//user sınıfına uygun yazılacak vb. düzenleme ve ekleme yapılcak.
void newUserAdd(t_IRC_DATA *data, std::map<int, User> &clientList){
	data->addrLen = sizeof(data->remoteAddr);
	if((data->newClientSocket = accept(data->serverSocket, (struct sockaddr *)&data->remoteAddr, &data->addrLen)) == -1)
		perror("accept");
	else{
		User newUser(data->newClientSocket);
		std::cout << "new user : " << newUser.gethostInfo() << std::endl;
		FD_SET(data->newClientSocket, &data->masterFds); // ana listeye ekle
		clientList.insert(std::pair<int, User>(data->newClientSocket, newUser));//map'ekleme
		if(data->newClientSocket > data->fdMax){
			data->fdMax = data->newClientSocket;
		}
		std::map<int, User>::iterator it = clientList.find(data->newClientSocket);
		std::cout << "new user" << it->second.gethostInfo() << std::endl;
		printf("selectserver: new connection from %s on "
			"socket %d\n", inet_ntoa(data->remoteAddr.sin_addr), data->newClientSocket);
	}
}