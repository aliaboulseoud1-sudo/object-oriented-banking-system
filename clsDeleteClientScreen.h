#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen {
private:
	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.getFullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.getAccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:
	static void ShowDeleteClientScreen() {
		if (!__CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
			return;      // this will exit the function and it will not continue
		}

		
		__DrawScreenHeader("\t  Delete Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Account number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\nAre you sure you want to delete this client y/n?";

		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			if (Client.Delete()) {
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client);
			}
			else {
				cout << "\nError! Client Was Not Deleted.\n";
			}
		}
	}
};