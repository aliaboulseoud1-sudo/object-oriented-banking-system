#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen {
private:
    static float _ReadRate() {
        cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadNumber<float>();
        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency) {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.getCountry();
        cout << "\nCode       : " << Currency.getCurrencyCode();
        cout << "\nName       : " << Currency.getCurrencyName();
        cout << "\nRate(1$)   : " << Currency.getRate();
        cout << "\n_____________________________\n";
    }

public:
    static void ShowUpdateCurrencyRateScreen() {
        __DrawScreenHeader("   Update Currency Rate Screen");

        string CurrencyCode = "";

        cout << "\n\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
            cout << "\n\nPlease Enter Correct Currency Code: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        _PrintCurrency(Currency);

        char Answer = 'n';
        cout << "\nAre you sure want to update the rate of this currency (Y/N)? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            cout << "\n\nUpdate Currency Rate: \n";
            cout << "______________________\n\n";

            Currency.UpdateRate(_ReadRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
        }
        else {
            cout << "\n\nUpdate Currency Rate Operation Canceled.\n";
        }
    }
};

