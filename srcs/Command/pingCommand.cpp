#include "../../include/IRC.hpp"

void commandPing(std::string pingMessage, User &user){
    std::string pongMessage = "PONG " + pingMessage.substr(5) + "\r\n";
    std::cout << "PONG : " << pongMessage << std::endl;
    send(user.getClientSocket(), pongMessage.c_str(), pongMessage.length(), 0);
}