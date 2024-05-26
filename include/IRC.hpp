#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


#define BACKLOG 100
#define BUFFER_SIZE 1024
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

//Start Config
bool portCheck(t_IRC_DATA *data, std::string port);
void fillData(t_IRC_DATA *data, std::string passwordInput);

//IRC
void ircStart(t_IRC_DATA *data);
void newUserAdd(t_IRC_DATA *data);
void msgHandle(t_IRC_DATA *data, int userFD);
#endif