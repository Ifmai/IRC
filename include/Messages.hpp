#ifndef MESSAGES_HPP
	#define MESSAGES_HPP

	#define DEFAULT_KICK_MSG(channel, nick) ("You have been kicked out of the " + channel + " channel by" + nick + "\r\n")

	#define ERR_NEEDMOREPARAMS(command) (": 461 " + command + " : Not enough parameters!\r\n")
	#define ERR_NEEDMOREPARAMS_MODE_VALUE(command) (": 461 " + command + " : Need mode parameters!\r\n")
	#define ERR_NEEDMOREPARAMS_KICK_USER(command) (": 461 " + command + " : Need user nick name!\r\n")
	#define ERR_ALREADYREGISTERED() (": 462 :You may not reregister!\r\n")
	#define ERR_PASSWDMISMATCH() (": 464 : Password incorrect!\r\n")
	#define ERR_NICKNAMEINUSE(nickname) (": 433 " + nickname)
	#define ERR_ERRONEUSNICKNAME(nickname) (": 432 " + nickname + " : Invalid Nickname. Example : '#userNickName' or '12userNickName'\r\n")
	#define ERR_NOSUCHNICK(nickname) (": 401 " + nickname + " :No such nick\r\n")
	#define ERR_BADCHANNELKEY(channel) (": 475 " + channel + " : Cannot join channel (+k)\r\n")
	#define ERR_INVITEONLYCHAN(channel) (": 473 " + channel + " :Cannot join channel (+i)\r\n")
	#define ERR_CANNOTSENDTOCHAN(channel) (": 404 " + channel + " :Cannot send to channel\r\n")
	#define ERR_USERONCHANNEL(channel, nick) (": 443 " + nick + " " + channel + " :is already on channel\r\n")
	#define ERR_NOTONCHANNEL(channel) (": 442 " + channel + " :You're not on that channel\r\n")
	#define ERR_NOSUCHCHANNEL(channel) (": 403 " + channel + " :No such channel\r\n")
	#define ERR_INVALIDCHANNELNAME(channel) (": 403 " + channel + " :Channel names must start with '#' or '&'\r\n")
	#define RPL_NOTOPIC(channel) (": 331 " + channel + " :No topic is set\r\n")
	#define RPL_TOPIC(nick, channel, topic) (": 332 " + nick + " " + channel + " : " + topic + "\r\n")
	#define ERR_USERNOTINCHANNEL(nick, channel) (": 441 " + nick + " " + channel + " :They aren't on that channel\r\n")
	#define ERR_CHANOPRIVSNEEDED(channel) (": 482 " + channel + " :You're not channel operator\r\n")
	#define RPL_INVITING(nick, channel) (": 341 " + nick + " " + channel + " :Invite is successful\r\n")
	#define IDENTIY_USER(nickname,username,hostinfo) (":" + nickname + "!" + username + "@" + hostinfo + " ")
	#define LOGIN(nickname, username,hostinfo) (": 001 " + nickname + " :Welcome to the IRC Network " + nickname + "!" + username + "@" +hostinfo + "\r\n")
#endif