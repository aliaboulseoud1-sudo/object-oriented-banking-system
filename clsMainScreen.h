#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsInputValidate.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"
#include <iomanip>

using namespace std;


class clsMainScreen : protected clsScreen {
private:
    enum _enMainMenuOptions {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenu = 6,
        eManageUsers = 7,
        eLoginRegister = 8,
        eCurrencyExchange = 9,
        eExit = 10
    };

    static short _ReadMainMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }

    static void _GoBackToMainMenu() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to main menu...\n";
        system("pause>0");
        ShowMainMenu();
    }

    /*static void _ShowEndScreen() {
        cout << "\nEnd Screen Will Be Here...\n";
    }*/

    static void _Logout() {
        CurrentUser = clsUser::Find("", "");

        //then it will go back to main function.
    }

    static void _ShowTransactionsMenu() {
        // cout << "\nTransactions Menu Will Be Here...\n";

        clsTransactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowFindClientScreen() {
        // cout << "\nFind Client Screen Will Be Here...\n";

        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowUpdateClientScreen() {
        // cout << "\nUpdate Client Screen Will Be Here...\n";

        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowDeleteClientScreen() {
        // cout << "\nDelete Client Screen Will Be Here...\n";

        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowAddNewClientsScreen() {
        // cout << "\nAdd New Clients Screen Will Be Here...\n";

        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowAllClientsScreen() {
        // cout << "\nClient List Screen Will Be Here...\n";

        clsClientListScreen::ShowClientsList();
    }

    static void _ShowManageUsersMenu() {
        // cout << "\nManage Users Menu Will Be Here...\n";

        clsManageUsersScreen::ShowManageUsersMenu();
    }

    static void _ShowLoginRegisterScreen() {
      //  cout << "\nLogin Register Screen Will Be Here...\n";

        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMainScreen() {
       // cout << "\nCurrency Exchange Main Screen Will Be Here...\n";

        clsCurrencyExchangeMainScreen::ShowCurrenciesMenu();
    }

    static void _PerformMainMenuOption(_enMainMenuOptions MainMenuOption) {
        switch (MainMenuOption) {
        case _enMainMenuOptions::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eShowTransactionsMenu:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eCurrencyExchange:
            system("cls");
           _ShowCurrencyExchangeMainScreen();
            _GoBackToMainMenu();
            break;
        case _enMainMenuOptions::eExit:
            system("cls");
            _Logout();
            break;
        }
    }

public:
    static void ShowMainMenu() {
        system("cls");
        __DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenuOption((_enMainMenuOptions)_ReadMainMenuOption());
    }
};