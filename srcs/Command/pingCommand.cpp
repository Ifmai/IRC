#include "../../include/IRC.hpp"

void commandPing(std::string pingMessage, User &user){
    messageSend(user.getClientSocket(), "PONG " + pingMessage + "\r\n");
}

void commandCap(std::istringstream& iss, User& user){
    std::string capParameters;
    iss >> capParameters;

    if(capParameters == "LS"){
        std::string capLsCommand = "CAP * LS :multi-prefix sasl\r\n";
		messageSend(user.getClientSocket(), capLsCommand);
    }
    else if (capParameters == "REQ") {
        std::string reqParameter;
        iss >> reqParameter;
        if (reqParameter == ":multi-prefix") {
            std::string capAckCommand = "CAP * ACK :multi-prefix\r\n";
            messageSend(user.getClientSocket(), capAckCommand);
        }
    }
}