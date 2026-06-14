#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen {
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

        if (Permissions == 127) {
            return -1;
        }

        return Permissions;
    }

public:
    static void ShowUpdateUserScreen() {
        __DrawScreenHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter User UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        _PrintUser(User1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _ReadUserInfo(User1);

            clsUser::enSaveResults SaveResult;

            SaveResult = User1.Save();

            switch (SaveResult) {
            case  clsUser::enSaveResults::svSucceeded:
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User1);
                break;
            case clsUser::enSaveResults::svFaildEmptyObject:
                cout << "\nError user was not saved because it's empty!";
                break;
            }
        }
    }
};