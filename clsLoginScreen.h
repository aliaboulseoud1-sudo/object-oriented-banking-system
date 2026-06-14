#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include <fstream>
#include "clsDate.h"

using namespace std;

class clsLoginScreen : protected clsScreen {
private:
	static bool _Login() {
		bool LoginFailed = false;
		short FailedLoginCount = 0;

		string Username, Password;
		do {
			if (LoginFailed) {
				FailedLoginCount++;

				cout << "\nInvalid Username/Password!\n";
				cout << "You have " << (3 - FailedLoginCount) << " trial(s) to login.\n\n";
			}

			if (FailedLoginCount == 3) {
				cout << "\n\nYou are locked after 3 failed trials.\n";
				return false;
			}

			cout << "Enter Username? ";
			cin >> Username;

			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();
		} while (LoginFailed);

		CurrentUser.RegisterLogin();

		clsMainScreen::ShowMainMenu();
		return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		__DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

