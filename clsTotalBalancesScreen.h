#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include <iomanip>

using namespace std;

class clsTotalBalancesScreen : protected clsScreen {
private:
	static void _PrintClientRecordBalanceLine(clsBankClient Client) {
		cout << setw(25) << left << "" << "| " << setw(15) << left << Client.getAccountNumber();
		cout << "| " << setw(40) << left << Client.getFullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowTotalBalances() {
		vector <clsBankClient> vClients = clsBankClient::getClientsList();

		string Title = "\t  Balances List Screen";
		string SubTitle = "\t      (" + to_string(vClients.size()) + ") Client(s).";

		__DrawScreenHeader(Title, SubTitle);

		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(25) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(25) << left << "" << "\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		double TotalBalances = clsBankClient::getTotalBalances();

		if (vClients.size() == 0) {
			cout << "\t\t\t\tNo Clients Available In The System!";
		}
		else {
			for (clsBankClient Client : vClients) {
				_PrintClientRecordBalanceLine(Client);
				cout << endl;
			}
		}

		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
		cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ")";
	}
};