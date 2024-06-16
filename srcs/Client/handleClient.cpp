#include "../../include/IRC.hpp"



void handleClientQuit(t_IRC_DATA *data, int userFD, std::map<int, User> &clientList){
	close(userFD);
	FD_CLR(userFD, &data->masterFds);
	clientList.erase(clientList.find(userFD));
}

void handleClient(t_IRC_DATA *data, int userFD, User &client, std::map<int, User> &clientList, std::list<Channel> &channelList){
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
				commandPass(iss, client, clientList, data);
			else if(token == "NICK")
				commandNick(iss, client, clientList);
			else if(token == "USER")
				commandUser(iss, client);
			if(!client.getPassword().empty() && !client.getName(USER_NAME).empty() && !client.getName(USER_NICK_NAME).empty() && !client.getIsAuth()){
				client.setIsAuth(true);
				messageSend(client.getClientSocket(), LOGIN(client.getName(USER_NICK_NAME), client.getName(USER_NAME), client.gethostInfo()));
			}
			else if(token == "PING" && client.getIsAuth()){
				std::string msg = data->buff;
				commandPing(msg, client);
			}
			if(client.getIsAuth() && token == "PRIVMSG")
				commandMSG(token, iss, client,clientList, channelList);
			else if(client.getIsAuth() && token == "JOIN")
				commandJoin(iss, channelList, client, clientList);
			else if(client.getIsAuth() && token == "TOPIC")
				commandTopic(iss ,channelList, client);
			else if(client.getIsAuth() && token == "KICK")
				commandKick(iss, channelList, client, clientList);
			else if(client.getIsAuth() && token == "LIST")
				commandList(iss, channelList, client, clientList);
			else if(client.getIsAuth() && token == "INVITE")
				commandInvite(iss, channelList, client, clientList);
			else if(client.getIsAuth() && token == "MODE")
				commandMode(iss, channelList, client, clientList);
			else if(client.getIsAuth() && token == "PART")
				commandPart(iss, client, channelList, clientList);
			else if(client.getIsAuth() && token == "QUIT")
				commandQuit(iss, client, channelList, clientList, data);
		}
	}
}

/*
PASS asd USER alp1 NICK alp
PASS asd USER berna1 NICK berna
PRIVMSG berna alp <3
PRIVMSG alp berna <3
*/