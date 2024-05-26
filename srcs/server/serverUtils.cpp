#include "../../include/IRC.hpp"


void sendMsg(int socketFD, const void * msg, size_t msgLen, int flag = 0){
	if(send(socketFD, msg, msgLen, flag) == -1)
		perror("send");
}
