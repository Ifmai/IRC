#ifndef CHANNEL_HPP
    #define CHANNEL_HPP

    #include <map>
    #include <iostream>
    #include <list>
    #include "User.hpp"

    class Channel{
        private:
            std::string                     channelName;
            std::string                     channelType;
            std::string                     channelKey;
            std::list<int>                  clientList;
            std::list<std::string>          channelMode;
            std::list<std::string>          inviteList;
            std::list<int>                  channelModerator;


            bool                            isInvite;
            bool                            keyExist;
        public:
            Channel(std::string name, std::string type, std::string key, int clientFd);
            Channel(std::string name, std::string type, int clientFd);
			Channel(const Channel& copy);
			Channel& operator=(const Channel& copy);
			~Channel();

            std::string getName();
            std::string getChannelType();
//            std::string getChannelMode();
            bool        getisInvite();
            bool        checkClient(int fd);
    };

    bool checkList(std::string channel, std::list<Channel> &channelList);
    Channel& getChannel(std::list<Channel> &channelList, std::string channel);

#endif

// # standart kanal türü. 
// & sadece aynı local sunucudaki clientlerin girebildiği sunucu tipi.
