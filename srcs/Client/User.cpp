#include "../../include/User.hpp"

User::User():clientSocket(-1), userName(""), nickName(""), \
	 realName(""), password(""), isAuth(false){}

User::User(int clientFd):clientSocket(clientFd),  userName(""), nickName(""), \
		realName(""), password(""), isAuth(false){
	char str_h[256];
    gethostname(str_h, sizeof(str_h));
	std::string info(str_h);
	this->hostInfo = info;
}

User::User(const User& copy):clientSocket(copy.clientSocket), userName(copy.userName), nickName(copy.nickName), \
	 realName(copy.realName), hostInfo(copy.hostInfo), password(copy.password), isAuth(copy.isAuth){}

User& User::operator=(const User& copy){
	if(this == &copy)
		return *this;

	this->clientSocket = copy.clientSocket;
	this->userName = copy.userName;
	this->nickName = copy.nickName;
	this->realName = copy.realName;
	this->password = copy.password;
	this->hostInfo = copy.hostInfo;
	this->isAuth = copy.isAuth;
	return *this;
}

User::~User(){}

//Get Member
int User::getClientSocket(){
	return this->clientSocket;
}

bool User::getIsAuth(){
	return this->isAuth;
}

std::string User::getPassword(){
	return this->password;
}

std::string User::gethostInfo(){
	return this->hostInfo;
}

std::string User::getName(int nameType){
	switch (nameType)
	{
		case USER_NAME:
			return this->userName;
			break;
		case USER_NICK_NAME:
			return this->nickName;
			break;
		case USER_REAL_NAME:
			return this->realName;
			break;
		case USER_HOST_INFO:
			std::cout << "hostinfo : " << this->hostInfo << std::endl;
			return this->hostInfo;
			break;
		default:
			return "Invalid input. Input list <USER_NAME, USER_NICK_NAME, USER_REAL_NAME, USER_HOST_NAME>";
			break;
	}
}

//Set Member
void User::setIsAuth(bool input){
	this->isAuth = input;
}

void User::setPassword(std::string pass){
	this->password = pass;
}

void User::setName(int nameType, std::string inputName){
	switch (nameType)
	{
		case USER_NAME:
			this->userName = inputName;
			break;
		case USER_NICK_NAME:
			this->nickName = inputName;
			break;
		case USER_REAL_NAME:
			this->realName = inputName;
			break;
		default:
			std::cout << "Invalid input. Input list <USER_NAME, USER_NICK_NAME, USER_REAL_NAME, USER_HOST_NAME, USER_PASS>" << std::endl;
			break;
	}
}

User* searchNick(const std::string &nick, std::map<int, User> &clientList){
	std::map<int, User>::iterator it = clientList.begin();
	while(it != clientList.end()){
		if(it->second.getName(USER_NICK_NAME) == nick)
			return &it->second;
		else
			it++;
	}
	return nullptr;
}