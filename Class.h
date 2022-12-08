#pragma once
#include<vector>
#include<cassert>
#include"Func.h"


class Users
{
	std::string _name;
	const std::string _login;
	std::string _password;
	//size_t _size = 0;
	
public:

	Users();
	Users(const std::string& name, const std::string& login, const std::string& password);
	~Users();
		
	std::string getName() const;
	std::string getLogin() const;
	std::string getPassword() const;
	void setName(std::string name);	
	void setPassword(std::string pass);
};


//############################################################################################
class Messages
{
	std::string _from;
	std::string _to;
	std::string _text;
	
public:
	Messages();
	Messages(std::string from, std::string to, std::string text);
	~Messages();
	
	std::string getFrom() const;	
	std::string getTo() const;
	std::string getText() const;	
};

//#############################################################################

class Chat
{
	std::vector <Messages> _chat_message;
	std::vector <Messages> _chat_message_all;
	std::vector<Users>_data_users;
	//size_t _size = 0;

public:
	Chat();
	~Chat();
		
	std::string signUp();
	std::string entrance();
	template <typename T> void abonentList(T& login_from);
	bool correctInputAbonent(std::string login_to);
	void messageInputAll(std::string login_from);
	void messageInputFromTo(std::string& login_from);
	void messageReadPersonal(std::string login_from);
	void messageReadAll();
	void messageWriteRead(std::string login_from);	
	Users& operator[](size_t index);	
};
