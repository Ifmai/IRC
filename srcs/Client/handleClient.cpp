#include "../../include/IRC.hpp"


//düzenlenicek parserler eklenicek commandler vb.

void handleClientQuit(t_IRC_DATA *data, int userFD, std::map<int, User> &clientList){
	close(userFD);
	FD_CLR(userFD, &data->masterFds);
	clientList.erase(clientList.find(userFD));
	//Birde channelda varsa o listeden de silincek.
}

void handleClient(t_IRC_DATA *data, int userFD, std::map<int, User> &clientList){
	if((data->nbytes = recv(userFD, data->buff,sizeof(data->buff), 0)) <= 0){
		if(data->nbytes == 0)
			printf("select server: socket %d hung up\n", userFD);
		else
			perror("recv");
		handleClientQuit(data, userFD, clientList);
	}
	else{
		data->buff[data->nbytes] = '\0';
		std::cout << "Client : " << userFD << " -> request : \"" << data->buff << "\"" << std::endl;
		std::istringstream iss(data->buff);
		std::string token;
		while(iss >> token){
			if(token == "PASS")
				commandPass(iss, clientList.find(userFD)->second, clientList, data);
			else if(token == "NICK")
				commandNick(iss, clientList.find(userFD)->second, clientList);
			else if(token == "USER")
				commandUser(iss, clientList.find(userFD)->second, clientList);
		}
	}
}