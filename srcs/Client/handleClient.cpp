#include "../../include/IRC.hpp"

void handleClientQuit(t_IRC_DATA *data, int userFD, std::map<int, User> &clientList){
	close(userFD);
	FD_CLR(userFD, &data->masterFds);
	clientList.erase(clientList.find(userFD));
}

static bool deleteEof(std::string &input, int userFD, t_IRC_DATA *data){
	if(input.at(data->nbytes - 1) != '\n'){
		data->check = data->message.find(userFD);
		if(data->check != data->message.end())
			data->check->second += input.data();
		else
			data->message.insert(std::pair<int, std::string>(userFD, input));
		return true;
	}
	else{
		data->check = data->message.find(userFD);
		if(data->check != data->message.end())
			data->check->second += input.data();
		return false;
	}
}

void handleClient(t_IRC_DATA *data, int userFD, User &client, std::map<int, User> &clientList, std::list<Channel> &channelList){
	std::istringstream iss;
	if((data->nbytes = recv(userFD, data->buff,sizeof(data->buff), 0)) <= 0){
		if(data->nbytes == 0)
			std::cout << "select server: socket " << userFD  << " hung up" << std::endl;
		else
			perror("recv");
		handleClientQuit(data, userFD, clientList);
	}               
	else{
		data->buff[data->nbytes] = '\0';
		std::string recv_msg(data->buff);
		std::cout << recv_msg << std::endl;
		if(!deleteEof(recv_msg, userFD, data)){
			data->check = data->message.find(userFD);
			if(data->check != data->message.end()){
				iss.str(data->check->second);
				data->message.erase(data->check);
			}
			else
				iss.str(recv_msg);
		}
		//std::cout << "Client : " << userFD << " -> request : \"" << data->buff << "\"" << std::endl;
		std::string token;

		while(iss >> token){
			if(token == "CAP")
				commandCap(iss, client);
			else if(token == "PASS")
				commandPass(iss, client, clientList, data);
			else if(token == "NICK")
				commandNick(iss, client, clientList);
			else if(token == "USER") // toplu bir anlık girşi checkle
				commandUser(iss, client);
			else if(token == "PING"){
				std::string msg = fullMsg(iss);
				commandPing(msg, client);
				continue;
			}
			else if(client.getIsAuth() == false){
				if((token != "PRIVMSG" && token != "JOIN" && token != "TOPIC" && token != "KICK" && token != "INVITE" && token != "LIST" && token != "MODE" && token != "PART" && token != "QUIT"))
					messageSend(client.getClientSocket(), client.getIDENTITY() + "COMMAND 1NOT FOUND.\r\n");
				else
					messageSend(client.getClientSocket(), client.getIDENTITY() + "PLEASE LOGIN FIRST.\r\n");
				while(iss >> token);
			}
			if(!client.getPassword().empty() && !client.getName(USER_NAME).empty() && !client.getName(USER_NICK_NAME).empty() && !client.getIsAuth()){
				std::string loginCommand = LOGIN(client.getName(USER_NICK_NAME), client.getName(USER_NAME), client.gethostInfo());
        		messageSend(client.getClientSocket(), loginCommand);
				client.setIsAuth(true);
				continue;
				//messageSend(client.getClientSocket(), LOGIN(client.getName(USER_NICK_NAME), client.getName(USER_NAME), client.gethostInfo()));
			}

			if(client.getIsAuth() && token == "PRIVMSG")
				commandMSG(token, iss, client,clientList, channelList);
			else if(client.getIsAuth() && token == "JOIN")
				commandJoin(iss, channelList, client);
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
			else if(client.getIsAuth() && token == 	"NOTICE")
				commandMSG(token, iss, client,clientList, channelList);
			else if(client.getIsAuth()){
				messageSend(client.getClientSocket(), client.getIDENTITY() + "COMMAND NOT FOUND.\r\n");
			}
		}
	}
}

/*
PASS asd USER alp1 NICK alp
PASS asd USER berna1 NICK berna
PRIVMSG berna alp <3
PRIVMSG alp berna <3
*/