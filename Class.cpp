#include"Class.h"

HANDLE hConsole;

Users::Users() = default;
Users::Users(const std::string& name, const std::string& login, const std::string& password)
	: _name(name), _login(login), _password(password) {};
Users::~Users() = default;

std::string Users::getName() const { return _name; }
std::string Users::getLogin() const { return _login; }
std::string Users::getPassword() const { return _password; }
void Users::setName(std::string name) { _name = name; }
void Users::setPassword(std::string pass) {	_name = pass; }

//############################################################################################

Messages::Messages() = default;
Messages::Messages(std::string from, std::string to, std::string text) : _from(from), _to(to), _text(text) {};
Messages::~Messages() = default;

std::string Messages::getFrom() const { return _from; }
std::string Messages::getTo() const { return _to; }
std::string Messages::getText() const { return _text; }

//#############################################################################

Chat::Chat() = default;
Chat::~Chat() = default;
		
std::string Chat::signUp()
{
	std::string name = inputName();
	std::string login = inputLogin();
	std::string password = inputPass();
	Users user(name, login, password);
	auto count = 0;
	if (_data_users.size())
	{
		for (auto i = 0; i < _data_users.size(); ++i)
		{
			if (login == _data_users[i].getLogin())
			{
				count++;
				std::cout << "Такие имя/логин/пароль уже зарегистрированы.\n Попробуйте еще раз. ";
				std::cout << std::endl;
				return "error";
			}
		}
		if (!count)
		{
			_data_users.push_back(user);
			std::cout << "Поздравляем, " << user.getName() << ", вы успешно зарегистрированы. \n";
		}
	}
	else
	{
		_data_users.push_back(user);
		std::cout << "Поздравляем, " << user.getName() << ", регистрация прошла успешно. \n";
	}
	return  user.getLogin();
}
	
std::string Chat::entrance()
{		
	auto count = 0;
	if (!_data_users.empty())
	{
		std::string login = inputLogin();
		std::string password = inputPass();

		for (auto i = 0; i < _data_users.size(); ++i)
		{

			if (login == _data_users[i].getLogin() && password == _data_users[i].getPassword())
			{
				count++;
			}
		}
		if (count)
		{
			std::cout << "Вход выполнен успешно" << std::endl;
			return login;
		}
		else
		{
			std::cout << "Такого логина/пароля нет" << std::endl;
			return "error";
		}
	}
	else
	{
		std::cout << "Сначала зарегистрируйтесь." << std::endl;
		return "error";
	}
}
	
template <typename T> void Chat::abonentList(T& login_from)
{
	std::cout << "Абоненты:   всем    ";
	for (auto i = 0; i < _data_users.size(); ++i)
	{
		if (login_from != _data_users[i].getLogin())
		{
			std::cout << _data_users[i].getLogin() << '\t';
		}
	}
}
	
bool Chat::correctInputAbonent(std::string login_to)
{

	for (auto i = 0; i < _data_users.size(); ++i)
	{
		if (login_to == _data_users[i].getLogin())
			return true;
	}
	return false;
}
	
void Chat::messageInputAll(std::string login_from)
{		
	std::string text = massageText();
	_chat_message_all.push_back({ "всем", login_from, text });		
}
	
void Chat::messageInputFromTo(std::string& login_from)	{
	std::string text;
	std::string login_to;

	abonentList<std::string>(login_from);
	login_to = inputTo();
	if (login_to == "всем")
	{
		messageInputAll(login_from);
	}
	else
	{
		if (correctInputAbonent(login_to))
		{
			text = massageText();
			_chat_message.push_back({ login_from, login_to, text });
		}
		else
		{
			incorrectInputMenuMessage();
		}
	}
}

void Chat::messageReadPersonal(std::string login_from)	{
	auto count = 0;
	if (_chat_message.size())
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);			
		std::cout << "Личные сообщения:     " << std::endl;
		for (auto i = 0; i < _chat_message.size(); ++i)
		{
			SetConsoleTextAttribute(hConsole, 2);
			if (login_from == _chat_message[i].getTo())
			{
				std::cout << "От кого: " << _chat_message[i].getFrom() << "   >>  " << _chat_message[i].getText() << std::endl;
				count++;
			}
		}
		SetConsoleTextAttribute(hConsole, 7);
		if (!count) { noMessages(); }
	}
	else
	{
		noMessages();
	}
}

void Chat::messageReadAll()
{
	if (_chat_message_all.size())
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);			
		std::cout << "Сообщения из общего чата:     "<< std::endl;
		SetConsoleTextAttribute(hConsole, 9);
		for (auto i = 0; i < _chat_message_all.size(); ++i)
		{
			std::cout << "От кого:   " << _chat_message_all[i].getTo() << '\t' << " >>  "
				<< _chat_message_all[i].getText() << std::endl;
		}
		SetConsoleTextAttribute(hConsole, 7);
	}
	else
	{
		std::cout << "Сообщений из общего чата нет. " << std::endl;
	}
}

void Chat::messageWriteRead(std::string login_from)
{
	std::string text;
	char choice;
	std::string login_to;
	do
	{
		choice = menuMessage();
		switch (choice)
		{
		case '1':
			messageReadAll();
			messageReadPersonal(login_from);
			break;

		case '2':
			messageInputFromTo(login_from);
			break;

		case '3':
			system("cls");
			break;
		default:
			incorrectInputMenuMessage();
			break;
		}
	} while (choice != '3');

}

Users& Chat::operator[](size_t index)
{
	assert(index > 0 && index > _data_users.size());
	return _data_users[index];
}


