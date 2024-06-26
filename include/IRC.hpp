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
		fd_set				readFds; // select for while.
		fd_set				masterFds; // all user in.
		struct sockaddr_in	serverAddr; // server adress info.
		struct sockaddr_in	remoteAddr; // new user address info.
		char				buff[BUFFER_SIZE]; // recv buffer string.
		std::string			password; // connection password.
		socklen_t			addrLen; // new user addr len.
		int					yes; // for setsockopt()SO_REUSEADDR.
		int					port; // connection port.
		int 				fdMax; // select max fd number.
		int					nbytes; //recv buffer string len.
		int					serverSocket; // server socket.
		int					newClientSocket; // new user.

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