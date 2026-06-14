#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsTransferScreen : protected clsScreen {
private:
	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n___________________\n";
		cout << "\nFull Name   : " << Client.getFullName();
		cout << "\nAcc. Number : " << Client.getAccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber(string Message) {
		string AccountNumber;

		cout << Message;
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient) {
		double Amount;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate::ReadNumber<double>();

		while (Amount > SourceClient.AccountBalance) {
			cout << "\nAmount exceeds the available balance, enter another amount ? ";
			Amount = clsInputValidate::ReadNumber<double>();
		}

		return Amount;
	}

public:
	static void ShowTransferScreen() {
		__DrawScreenHeader("\tTransfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer From: "));
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer To: "));
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		cout << "\nAre you sure you want to perform this operation (Y/N)? ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName)) {
				cout << "\nTransfer Done Successfully -:)\n";
			}
			else {
				cout << "\nTransfer Failed (:-\n";
			}

			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);
		}
		else {
			cout << "\n\nTransfer Canceled.";
		}
	}
};

