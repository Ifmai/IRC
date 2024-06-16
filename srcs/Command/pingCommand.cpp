#include "../../include/IRC.hpp"

void commandPing(std::string pingMessage, User &user){
    messageSend(user.getClientSocket(), "PONG " + pingMessage.substr(5) + "\r\n");
}