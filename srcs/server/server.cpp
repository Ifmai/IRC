#include "../../include/IRC.hpp"

static void serverConfig(t_IRC_DATA *data){
	if((data->serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}
	if (setsockopt(data->serverSocket, SOL_SOCKET, SO_REUSEADDR, &data->yes,sizeof(int)) == -1) {
    	perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	if(fcntl(data->serverSocket, F_SETFL, O_NONBLOCK) == -1){
		perror("fcntl F_SETFL");
		exit(EXIT_FAILURE);
	}
	data->serverAddr.sin_family = AF_INET;
	data->serverAddr.sin_addr.s_addr = INADDR_ANY;
	data->serverAddr.sin_port = htons(data->port);
	memset(&(data->serverAddr.sin_zero), '\0', 8);
	if(bind(data->serverSocket, (struct sockaddr *)&data->serverAddr, sizeof(data->serverAddr)) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if(listen(data->serverSocket, BACKLOG) == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}
	FD_SET(data->serverSocket, &data->masterFds); 
	data->fdMax = data->serverSocket; // so far, it’s this one
	std::cout << "Server is listening on port \"" << data->port << "\"" << std::endl;
	std::cout << "Print Start Log." << std::endl;
	std::cout << "----------------" << std::endl;
}

/* void	printList(std::map<int, User> list){
	std::map<int, User>::iterator it = list.begin();
	while(it != list.end()){
		std::cout << "["<< it->first << "] : " << it->second.getClientSocket() << std::endl;
		it++;
	}
}
 */

void ircStart(t_IRC_DATA *data){
	serverConfig(data);
	std::map<int, User> clientList; // pair kaynaklı list'e çevrilebilir.
	//std::list<Channel> channelList;
	while(true){
		data->readFds = data->masterFds; // kopyalıyoruz çünkü select bozuyor işlem yaparken.
		if(select(data->fdMax+1, &data->readFds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(EXIT_FAILURE);
		}
		for(int i = 0; i <= data->fdMax; i++){
			if(FD_ISSET(i, &data->readFds)){
				if(i == data->serverSocket)
					newUserAdd(data, clientList);
				else
					handleClientRequest(data, i, clientList);
			}
		}
	}
}