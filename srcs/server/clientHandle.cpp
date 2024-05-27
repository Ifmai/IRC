#include "../../include/IRC.hpp"


//düzenlenicek parserler eklenicek commandler vb.

void handleClientRequest(t_IRC_DATA *data, int userFD, std::map<int, User> &clientList){
	if((data->nbytes = recv(userFD, data->buff,sizeof(data->buff), 0)) <= 0){
		if(data->nbytes == 0)
			printf("select server: socket %d hung up\n", userFD);
		else
			perror("recv");
		close(userFD);
		FD_CLR(userFD, &data->masterFds);
		clientList.erase(clientList.find(userFD));
	}
	else{

	}
}




/* void msgHandle(t_IRC_DATA *data, int userFD){
	if((data->nbytes = recv(userFD, data->buff,sizeof(data->buff), 0)) <= 0){
		if(data->nbytes == 0)
			printf("select server: socket %d hung up\n", userFD);
		else
			perror("recv");
		close(userFD);
		FD_CLR(userFD, &data->masterFds);
	}
	else{
		for(int i = 0; i <= data->fdMax; i++){
			if(FD_ISSET(i, &data->masterFds)){
				if(i != data->serverSocket && i != userFD){
					if(send(i, data->buff, data->nbytes, 0) == 1)
						perror("send");
				}
			}
		}
	}
}
//çok çirkin oldu bunun daha güzel yazımı olması lazım! */