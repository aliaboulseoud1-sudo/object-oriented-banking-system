#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

using namespace std;

class clsAddNewUserScreen : protected clsScreen {
private:
    static void _ReadUserInfo(clsUser& User) {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.getFullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

    static int _ReadPermissionsToSet() {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nLogin Register (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        cout << "\nCurrency Exchange (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Permissions += clsUser::enPermissions::pCurrencyExchange;
        }

        if (Permissions == 511) {
            return -1;
        }

        return Permissions;
    }

public:
    static void ShowAddNewUserScreen() {
        __DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName)) {
            cout << "\nUserName Is Already Used, Choose Another One: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::getAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult) {
        case clsUser::enSaveResults::svSucceeded:
            cout << "\nUser Added Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "\nError User Was Not Saved Because It's Empty!";
            break;
        case clsUser::enSaveResults::svFailedUserExists:
            cout << "\nError User Was Not Saved Because UserName Is Used!\n";
            break;
        }
    }
};