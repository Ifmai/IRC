CC = c++ -std=c++98
FLAG = -Wall -Wextra -Werror 
Name = IRC
SRC = ./srcs/main.cpp \
	  ./srcs/server/server.cpp \
	  ./srcs/server/newUserHandle.cpp \
	  ./srcs/argCheck/fillData.cpp \
	  ./srcs/argCheck/inputCheck.cpp \
	  ./srcs/Client/handleClient.cpp \
	  ./srcs/Client/User.cpp \
	  ./srcs/Channel/Channel.cpp \
	  ./srcs/Command/nickCommand.cpp \
	  ./srcs/Command/passCommand.cpp \
	  ./srcs/Command/userCommand.cpp \
	  ./srcs/Command/msgCommand.cpp \
	  ./srcs/Command/joinCommand.cpp
all: $(Name)

$(Name): $(SRC)
	@echo "Compiling..."
	@$(CC) $(FLAG) $(SRC) -o $(Name)

clean:
	@echo "Cleaning..."
	@rm -rf $(Name)

fclean: clean

re: fclean all

.PHONY: all clean fclean re