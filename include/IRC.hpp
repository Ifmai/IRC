#ifndef IRC_HPP
	#define IRC_HPP

	#include <iostream>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <fcntl.h>
	#include <sstream>
	#include <list>


	#include "Channel.hpp"

	#define BACKLOG 100
	#define BUFFER_SIZE 512

	typedef struct s_IRC
	{
		fd_set				readFds; 
		fd_set				masterFds; 
		struct sockaddr_in	serverAddr;
		struct sockaddr_in	remoteAddr;
		char				buff[BUFFER_SIZE];
		std::string			password;
		socklen_t			addrLen; 
		int					yes; 
		int					port;
		int 				fdMax;
		int					nbytes;
		int					serverSocket;
		int					newClientSocket;
		std::map<int, std::string> message;
		std::map<int, std::string>::iterator check;
	}						t_IRC_DATA;

	//Arguman Checking
	bool portCheck(t_IRC_DATA *data, std::string port);
	void fillData(t_IRC_DATA *data, std::string passwordInput);
	

	//IRC
	void ircStart(t_IRC_DATA *data);

	void handleClient(t_IRC_DATA *data, int userFD, User &client, std::map<int, User> &clientList, std::list<Channel> &channelList);
		void newUserAdd(t_IRC_DATA *data, std::map<int, User> &clientList);
		void handleClientQuit(t_IRC_DATA *data, int userFD, std::map<int, User> &clientList);
		void commandNick(std::istringstream &iss, User &client, std::map<int, User> &clientList);
		void commandPass(std::istringstream &iss, User &client, std::map<int, User> &clientList, t_IRC_DATA *data);
		void commandUser(std::istringstream &iss, User &client);
		void commandPing(std::string pingMessage, User &user);

		void commandMSG(std::string &token, std::istringstream &iss, User &client, std::map<int, User> &clientList, std::list<Channel> channelList);
		void commandJoin(std::istringstream &iss, std::list<Channel> &channelList, User &user);
		void commandTopic(std::istringstream &iss, std::list<Channel> &channelList, User &user);
		void commandKick(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &clientList);
		void commandList(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList);
		void commandInvite(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList);
		void commandMode(std::istringstream &iss, std::list<Channel> &channelList, User &user, std::map<int, User> &userList);
		void commandPart(std::istringstream &iss, User &user, std::list<Channel> &channelList, std::map<int, User> &userList);
		void commandQuit(std::istringstream &iss, User &user, std::list<Channel> &channelList, std::map<int, User> &userList, t_IRC_DATA *data);
		void commandCap(std::istringstream& iss, User& user);
	
	//Comand Utils
	std::string fullMsg(std::istringstream &iss);
	void messageSend(int targetFd, std::string msg);
	void sendAllUserMsg(std::map<int, User> &userList, std::string &msg);
#endif