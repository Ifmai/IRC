#ifndef CHANNEL_HPP
    #define CHANNEL_HPP

    #include <map>
    #include <iostream>
    #include <list>
    #include "User.hpp"
	#include <sys/socket.h>
    #include "Messages.hpp"

    class Channel{
        private:
            std::string                     channelName;
            std::string                     channelType;
            std::list<std::string>          channelMode;
            std::string                     channelKey;
            std::list<int>                  clientList;
            std::list<int>                  inviteList;
            std::list<int>                  channelModerator;

            bool                            isPublic;
            bool                            isInvite;
            bool                            keyExist;
        public:
            Channel(std::string name, std::string type, int clientFd);
			Channel(const Channel& copy);
			Channel& operator=(const Channel& copy);
			~Channel();

            void        sendMsgChannel(std::string msg, int senderFd);
            void        newJoinMsg(int userFd, std::map<int, User> userList);

            std::string getName();
            std::string getChannelType();
            std::string getKey();
            bool        getKeyExist();
            bool        getisInvite();
            bool        getChannelMode(std::string mode);
            bool        getIsPublic();
            bool        getInviteList(int fd);

            void        setKey(std::string input);
            void        setIsPublic(bool input);
            void        setKeyExist(bool input);
            void        addChannelMode(std::string input);
            
            bool        checkClient(int fd);
            bool        checkClientMode(int fd);
            void        addInviteList(int fd);
            void        addModerator(int fd);
            void        removeModerator(int fd);
            void        removeChannelMode(std::string input);
            
    };

    bool checkList(std::string channel, std::list<Channel> &channelList);
    std::list<Channel>::iterator getChannel(std::list<Channel> &channelList, std::string channel);

#endif

// # standart kanal türü. 
// & sadece aynı local sunucudaki clientlerin girebildiği sunucu tipi.
