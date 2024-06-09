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

            std::string getName();
            std::string getChannelType();
            std::string getKey();
            bool        getKeyExist();
            bool        getisInvite();
            bool        checkClient(int fd);
            bool        getChannelMode(std::string mode);
            bool        getIsPublic();
            bool        getInviteList(int fd);
            
            void        addInviteList(int fd);
            void        setIsPublic(bool input);
            void        addModerator(int fd);
            void        removeModerator(int fd);
            void        addChannelMode(std::string input);
            void        removeChannelMode(std::string input);
            void        setKey(std::string input);
            void        setKeyExist(bool input);
    };

    bool checkList(std::string channel, std::list<Channel> &channelList);
    std::list<Channel>::iterator getChannel(std::list<Channel> &channelList, std::string channel);

#endif

// # standart kanal türü. 
// & sadece aynı local sunucudaki clientlerin girebildiği sunucu tipi.
