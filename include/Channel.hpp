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
            void        newJoinMsg(int userFd, std::map<int, User> userList);
            void        writeClientList(int sendFd, std::map<int, User> &userList);
            void        newJoinMsgALL(std::map<int, User> userList);
            void        checkModerator(std::map<int, User> &userList);

            void        printChannelMode(){
                std::list<std::string>::iterator as = this->channelMode.begin();
                while(as != this->channelMode.end()){
                    std::cout << "Mode Channel " + this->getName() + " " + *as << std::endl;
                    as++;
                }
            }
            void        printInviteList(){
                std::list<int>::iterator as = this->inviteList.begin();
                while(as != this->inviteList.end()){
                    std::cout << "Mode İNVİTE LİST FD  " + this->getName() + " " + std::to_string(*as) << std::endl;
                    as++;
                }
            }

            std::string getName();
            std::string getChannelType();
            std::string getKey();
            std::string getTopic();
            std::string getChangerTopic();
            int         getClientListSize();
            bool        getKeyExist();
            bool        getisInvite();
            bool        getChannelMode(std::string mode);
            bool        getIsPublic();
            bool        getInviteList(int fd);


            void        setChangerTopic(std::string nick);
            void        setTopic(std::string newTopic);
            void        setKey(std::string input);
            void        setIsPublic(bool input);
            void        setKeyExist(bool input);
            
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

    bool checkList(std::string channel, std::list<Channel> &channelList);
    std::list<Channel>::iterator getChannel(std::list<Channel> &channelList, std::string channel);

#endif

// # standart kanal türü. 
// & sadece aynı local sunucudaki clientlerin girebildiği sunucu tipi.
