#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen {
private:
    enum _enManageUsersMenuOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
    };

    static short _ReadManageUsersMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter number between 1 to 6? ");
        return Choice;
    }

    static void _GoBackToManageUsersMenu() {
        cout << "\n\nPress any key to go back to manage users menu...";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen() {
        // cout << "\nList Users Screen Will Be Here.\n";

        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen() {
        // cout << "\nAdd New User Screen Will Be Here.\n";

        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen() {
        // cout << "\nDelete User Screen Will Be Here.\n";

        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {
        // cout << "\nUpdate User Screen Will Be Here.\n";

        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen() {
        // cout << "\nFind User Screen Will Be Here.\n";

        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersMenuOption(_enManageUsersMenuOptions ManageUsersMenuOption) {
        switch (ManageUsersMenuOption) {
        case _enManageUsersMenuOptions::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case _enManageUsersMenuOptions::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case _enManageUsersMenuOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case _enManageUsersMenuOptions::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case _enManageUsersMenuOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case _enManageUsersMenuOptions::eMainMenu:
            //do nothing here the main screen will handle it :-)
            break;
        }
    }

public:
    static void ShowManageUsersMenu() {
        if (!__CheckAccessRights(clsUser::enPermissions::pManageUsers)) {
            return;      // this will exit the function and it will not continue
        }
        
        system("cls");
        __DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenuOption((_enManageUsersMenuOptions)_ReadManageUsersMenuOption());
    }
};