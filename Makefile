CC = c++ -std=c++98
FLAG = -Wall -Wextra -Werror 
Name = IRC
SRC = ./srcs/main.cpp \
	  ./srcs/server/server.cpp \
	  ./srcs/server/newUserHandle.cpp \
	  ./srcs/server/clientHandle.cpp \
	  ./srcs/mainUtils/fillData.cpp \
	  ./srcs/mainUtils/inputCheck.cpp \
	  ./srcs/user/User.cpp
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