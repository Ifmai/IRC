#ifndef MESSAGES_HPP
	#define MESSAGES_HPP

	// PASS ERROR
	#define ERR_NEEDMOREPARAMS(command) (": 461 " + command + " : Not enough parameters!")
	#define ERR_ALREADYREGISTERED() (": 462 :You may not reregister!")
	#define ERR_PASSWDMISMATCH() (": 464 : Password incorrect!")
	// NICK ERROR
	#define ERR_NICKNAMEINUSE(nickname) (": 433 " + nickname + " ")
	#define ERR_ERRONEUSNICKNAME(nickname) (": 432 " + nickname + " : Invalid Nickname. Example : '#userNickName' or '12userNickName'")
#endif