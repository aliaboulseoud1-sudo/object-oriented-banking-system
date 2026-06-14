#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen {
private:
	static double _ReadAmount() {
		cout << "\nEnter Amount to Exchange: ";
		double Amount = 0;

		Amount = clsInputValidate::ReadNumber<double>();
		return Amount;
	}

	static clsCurrency _getCurrency(string Message) {
		string CurrencyCode;
		cout << Message << endl;

		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {
		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.getCountry();
		cout << "\nCode          : " << Currency.getCurrencyCode();
		cout << "\nName          : " << Currency.getCurrencyName();
		cout << "\nRate(1$)      : " << Currency.getRate();
		cout << "\n_____________________________\n\n";
	}

	static void _PrintCalculationsResults(double Amount, clsCurrency Currency1, clsCurrency Currency2) {
		_PrintCurrencyCard(Currency1, "Convert from:");

		double AmountInUSD = Currency1.ConvertToUSD(Amount);

		cout << Amount << " " << Currency1.getCurrencyCode()
			<< " = " << AmountInUSD << " USD\n";

		if (Currency2.getCurrencyCode() == "USD") {
			return;
		}

		cout << "\nConverting from USD to:\n";

		_PrintCurrencyCard(Currency2, "To:");

		double AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << Amount << " " << Currency1.getCurrencyCode()
			<< " = " << AmountInCurrency2 << " " << Currency2.getCurrencyCode();
	}

public:
	static void ShowCurrencyCalculatorScreen() {
		char Continue = 'y';

		while (toupper(Continue) == 'Y') {
			system("cls");

			__DrawScreenHeader("  Currency Calculator Screen");

			clsCurrency CurrencyFrom = _getCurrency("\nPlease Enter Currency1 Code: ");
			clsCurrency CurrencyTo = _getCurrency("\nPlease Enter Currency2 Code: ");
			
			double Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another calculation? y/n ? ";
			cin >> Continue;
		}
	}
};

