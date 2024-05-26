CC = c++ -std=c++98
FLAG = -Wall -Wextra -Werror 
Name = IRC
SRC = ./srcs/main.cpp \
	  ./srcs/server/server.cpp \
	  ./srcs/server/newUser.cpp \
	  ./srcs/server/msgHandle.cpp \
	  ./srcs/generalUtils/fillData.cpp \
	  ./srcs/generalUtils/inputCheck.cpp
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