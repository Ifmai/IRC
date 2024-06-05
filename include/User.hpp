#ifndef USER_HPP
	#define USER_HPP

	#define USER_NAME 1
	#define USER_NICK_NAME 2
	#define USER_REAL_NAME 3
	#define USER_HOST_INFO 4

	#include <iostream>
	#include <map>
	#include <unistd.h>

	class User{
		private:
			int			clientSocket;
			std::string	userName;
			std::string	nickName;
			std::string	realName;
			std::string hostInfo;
			std::string	password;
			bool		isAuth;

			User();
		public:
			User(int clientFd);
			User(const User& copy);
			User& operator=(const User& copy);
			~User();

			int 		getClientSocket();
			//std::string getUserName();
			//std::string getNickName();
			//std::string getrealName();
			std::string gethostInfo();
			std::string getName(int nameType); //Name Type Defined in User.hpp top side.
			std::string	getPassword();
			bool		getIsAuth();

			void		setIsAuth(bool input);
			void		setPassword(std::string pass);
			void		setName(int nameType, std::string inputName);
			
	};

	User* searchNick(const std::string &nick, std::map<int, User> &clientList);
#endif