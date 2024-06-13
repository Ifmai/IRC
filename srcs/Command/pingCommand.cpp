#include "../../include/IRC.hpp"

void commandPing(std::string pingMessage, User &user){
    std::string pongMessage = "PONG " + user.getName(USER_NICK_NAME) + " " + pingMessage.substr(5) + "\r\n";
    std::cout << pongMessage << " gönderdim amk" << std::endl;
    send(user.getClientSocket(), pongMessage.c_str(), pongMessage.length(), 0);
}