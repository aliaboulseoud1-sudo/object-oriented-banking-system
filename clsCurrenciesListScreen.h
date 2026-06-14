#pragma once

#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;

class clsCurrenciesListScreen : protected clsScreen {
private:
	static void _PrintCurrencyRecordLine(clsCurrency Currency) {
		cout << "\t\t";
		cout << "| " << left << setw(30) << Currency.getCountry();
		cout << "| " << left << setw(8) << Currency.getCurrencyCode();
		cout << "| " << left << setw(45) << Currency.getCurrencyName();
		cout << "| " << left << setw(10) << Currency.getRate();
	}

public:
	static void ShowCurrenciesListScreen() {
		vector <clsCurrency> vCurrencies = clsCurrency::getCurrenciesList();

		string Title = "\t Currencies List Screen";
		string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";

		__DrawScreenHeader(Title, SubTitle);

		cout << setw(25) << left << "" << "\n\t\t____________________________________________________";
		cout << "_________________________________________________\n" << endl;
		cout << "\t\t";
		cout << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << "\n\t\t____________________________________________________";
		cout << "_________________________________________________\n\n" << endl;

		if (vCurrencies.size() == 0) {
			cout << "\t\t\t\tNo Currencies Available In The System!";
		}
		else {
			for (clsCurrency Currency : vCurrencies) {
				_PrintCurrencyRecordLine(Currency);
				cout << endl;
			}
		}

		cout << setw(25) << left << "" << "\n\t\t____________________________________________________";
		cout << "_________________________________________________\n" << endl;
	}
};

