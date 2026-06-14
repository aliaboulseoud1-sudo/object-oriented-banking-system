#pragma once

#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen {
private:
    static void _PrintCurrency(clsCurrency Currency) {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.getCountry();
        cout << "\nCode       : " << Currency.getCurrencyCode();
        cout << "\nName       : " << Currency.getCurrencyName();
        cout << "\nRate(1$)   : " << Currency.getRate();
        cout << "\n_____________________________\n";
    }

    static void _ShowResults(clsCurrency Currency) {
        if (!Currency.IsEmpty()) {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else {
            cout << "\nCurrency Is Not Found :-(\n";
        }
    }

public:
    static void ShowFindCurrencyScreen() {
        __DrawScreenHeader("\t  Find Currency Screen");

        short Answer = 1;
        cout << "\nFind By: [1] Code or [2] Country? ";
        cin >> Answer;

        if (Answer == 1) {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }
    }
};

