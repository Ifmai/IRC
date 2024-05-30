#include "../include/IRC.hpp"

int main(int ac, char **argv){
	if(ac != 3){
		std::cerr << "İnput Example : <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}
	else {
		t_IRC_DATA data;
		if(!portCheck(&data, argv[1])){
			std::cerr << "Port : <only numbers>" << std::endl;
			return (EXIT_FAILURE);
		}
		fillData(&data, argv[2]);
		ircStart(&data);
		return (EXIT_SUCCESS);
	}
}

