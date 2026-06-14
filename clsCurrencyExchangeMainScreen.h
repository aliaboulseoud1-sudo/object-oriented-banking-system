#pragma once

#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include <iomanip>

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen {
private:
    enum _enCurrenciesMainMenuOptions {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4,
        eMainMenu = 5
    };

    static short _ReadCurrenciesMainMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrenciesMainMenu() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to currency exchange main menu...\n";
        system("pause>0");
        ShowCurrenciesMenu();
    }

    static void _ShowCurrenciesListScreen() {
        // cout << "\nCurrencies List Screen Will Be Here...\n";

        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen() {
        // cout << "\Find Currency Screen Will Be Here...\n";

        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen() {
        // cout << "\nUpdate Currency Rate Screen Will Be Here...\n";

        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen() {
        // cout << "\nCurrency Calculator Screen Will Be Here...\n";

        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrenciesMainMenuOption(_enCurrenciesMainMenuOptions MainMenuOption) {
        switch (MainMenuOption) {
        case _enCurrenciesMainMenuOptions::eListCurrencies:
            system("cls");
           _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMainMenu();
            break;
        case _enCurrenciesMainMenuOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMainMenu();
            break;
        case _enCurrenciesMainMenuOptions::eUpdateCurrencyRate:
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMainMenu();
            break;
        case _enCurrenciesMainMenuOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMainMenu();
            break;
        case _enCurrenciesMainMenuOptions::eMainMenu:
            break;
        }
    }

public:
    static void ShowCurrenciesMenu() {
        if (!__CheckAccessRights(clsUser::enPermissions::pCurrencyExchange)) {
            return;      // this will exit the function and it will not continue
        }

        system("cls");
        __DrawScreenHeader("  Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrenciesMainMenuOption((_enCurrenciesMainMenuOptions)_ReadCurrenciesMainMenuOption());
    }
};

