#include "../../include/IRC.hpp"

void commandTopic(std::istringstream &iss, std::list<Channel> &channelList, User &user){
	std::string channel;
	std::string topic;
	
	if(iss >> channel){
		if(channel.at('#') || channel.at('&')){
			std::list<Channel>::iterator ch = getChannel(channelList, channel);
			if(ch != channelList.end()){
				if(ch->checkClient(user.getClientSocket())){
					topic = fullMsg(iss);
					if(topic.length() == 1 && topic.at(0) == ':'){
						ch->setTopic("");
						topic = RPL_NOTOPIC(channel);
            			ch->sendAllMsg(topic);
					}
					else if(topic.length() > 1){
						if(topic.at(0) == ':')
							topic.erase(0);
						ch->setTopic(topic);
						std::string msgTopic = RPL_TOPIC(user.getName(USER_NICK_NAME), channel, topic);
						ch->sendAllMsg(msgTopic);
					}
					else{
						std::string msgTopic = ch->getTopic();
            			send(user.getClientSocket(), msgTopic.c_str(), msgTopic.length(), 0);
					}
				}else
        			errMesageSend(user.getClientSocket(), ERR_NOTONCHANNEL(channel));
			}else
        		errMesageSend(user.getClientSocket(), ERR_NOSUCHCHANNEL(channel));

		}else
        	errMesageSend(user.getClientSocket(), ERR_INVALIDCHANNELNAME(channel));
	}else{
		std::string token = "TOPIC";
        errMesageSend(user.getClientSocket(), ERR_NEEDMOREPARAMS(token));
	}

}