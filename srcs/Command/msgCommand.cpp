#include "../../include/IRC.hpp"

void commandMSG(std::string &token, std::istringstream &iss, User &client, std::map<int, User> &clientList, std::list<Channel> channelList){
	std::string target;
	std::string msg;

	if(iss >> target){
		std::string sendMsg = fullMsg(iss);

		msg = client.getIDENTITY() + token + " " + target + " :" + sendMsg + "\r\n";
		if(target.at(0) == '#' || target.at(0) == '&'){ // Channel
			std::list<Channel>::iterator ch = getChannel(channelList, target);
			if(ch->checkClient(client.getClientSocket()))
				ch->sendMsgChannel(msg, client.getClientSocket());
			else
        		errMesageSend(client.getClientSocket(), ERR_CANNOTSENDTOCHAN(ch->getName()));
		}
		else{ // User to User
			std::map<int, User>::iterator sendClient = searchNick(target, clientList);
			if(sendClient != clientList.end())
				send(sendClient->second.getClientSocket(), msg.c_str(), msg.length(), 0);
			else if (token == "PRIVMSG")
        		errMesageSend(client.getClientSocket(), ERR_NOSUCHNICK(target));
		}
	}
	else if (token == "PRIVMSG")
        errMesageSend(client.getClientSocket(), ERR_NEEDMOREPARAMS(token));
}