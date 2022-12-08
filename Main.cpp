#include"Class.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string login;
	char choice_menu;
	Chat chat;

	do
	{
		choice_menu = mainMenu();
		incorrectInputMenu(choice_menu);
		if (choice_menu == '1')
		{
			 login = chat.signUp();
			 if (login != "error")
			 {
				 chat.messageWriteRead(login);
			 }
		}
		if (choice_menu == '2')
		{
			auto login = chat.entrance();
			if (login != "error")
			{
				chat.messageWriteRead(login);
			}			
		}
	} 
	while (choice_menu != '3');
	
	return 0;
}


