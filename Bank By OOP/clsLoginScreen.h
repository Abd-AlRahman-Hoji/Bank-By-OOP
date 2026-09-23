#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

	static  bool _Login()
	{
		bool LoginFaild = false;

		string Username, Password;
		short Trials = 3;

		do
		{


			if (LoginFaild)
			{
				Trials--;

				cout << "\nInvlaid Username/Password!\n";
				cout << "you have " << Trials << " Trials to Login\n\n";

			}
			if (Trials == 0)
			{
				cout << "\n\n\nyou are Locked after 3 Faild trials\n\n";
				
				return  false;
			}
			cout << "Enter Username? ";
			cin >> Username;

			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		
		return true;
	}

public:


	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();

	}

};
