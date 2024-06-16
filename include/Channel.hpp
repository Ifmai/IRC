#ifndef CHANNEL_HPP
    #define CHANNEL_HPP

    #include <map>
    #include <iostream>
    #include <list>
    #include "User.hpp"
	#include <sys/socket.h>
	#include "Messages.hpp"

	void messageSend(int targetFd, std::string msg);

    class Channel{
        private:
            std::string                     channelName;
            std::string                     channelType;
            std::list<std::string>          channelMode;
            std::string                     channelKey;
            std::map<int, bool>             clientList;
            std::list<int>                  inviteList;
            std::list<int>                  channelModerator;
            std::string                     channelTopic;
            std::string                     changerTopic;

            bool                            isPublic;
            bool                            isInvite;
            bool                            keyExist;
        public:
            Channel(std::string name, std::string type, int clientFd);
			Channel(const Channel& copy);
			Channel& operator=(const Channel& copy);
			~Channel();

            void        sendMsgChannel(std::string msg, int senderFd);
            void        sendAllMsg(std::string msg);
            void        newJoinMsg(User &user, std::map<int, User> userList);
            void        writeClientList(int sendFd, std::map<int, User> &userList);
            void        ensureModeratorPresence(std::map<int, User> &userList);


            bool        getChannelMode(std::string mode);
            std::string getName();
            std::string getChannelType();
            bool        getisInvite();
            bool        getInviteList(int fd);
            bool        getKeyExist();
            bool        getIsPublic();
            bool        getJoinChannel(int fd);
            std::string getKey();
            std::string getTopic();
            std::string getChangerTopic();
            int         getClientListSize();


            void        setChangerTopic(std::string nick);
            void        setTopic(std::string newTopic);
            void        setKey(std::string input);
            void        setIsPublic(bool input);
            void        setKeyExist(bool input);
            void        setJoinChannel(int fd);
            
            bool        checkClient(int fd);
            bool        checkClientMode(int fd);

            void        addChannelMode(std::string input);
            void        removeChannelMode(std::string input);
            void        addInviteList(int fd);
            void        removeInviteList(int fd);
            void        addModerator(int fd);
            void        removeModerator(int fd);
            void        addClientList(int fd);
            void        removeClientList(int fd);
    };

    std::list<Channel>::iterator getChannel(std::list<Channel> &channelList, std::string channel);

#endif