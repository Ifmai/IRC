#ifndef MESSAGES_HPP
	#define MESSAGES_HPP

	#define ERR_NEEDMOREPARAMS(command) (": 461 " + command + " : Not enough parameters!\r\n")
	#define ERR_ALREADYREGISTERED() (": 462 :You may not reregister!\r\n")
	#define ERR_PASSWDMISMATCH() (": 464 : Password incorrect!\r\n")
	#define ERR_NICKNAMEINUSE(nickname) (": 433 " + nickname)
	#define ERR_ERRONEUSNICKNAME(nickname) (": 432 " + nickname + " : Invalid Nickname. Example : '#userNickName' or '12userNickName'\r\n")
	#define ERR_NOSUCHNICK(client, nickname) (": 401 " + client + " " + nickname + " :No such nick\r\n")

	#define LOGIN(nickname, username) (": 001 " + nickname + " :Welcome to the IRC Network " + nickname + "!" + username + "\r\n")
#endif