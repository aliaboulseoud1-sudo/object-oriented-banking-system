#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson {
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDeleted = false;

	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#") {
		stTransferLogRecord TransferLogRecord;

		vector <string>TransferLogDataLine = clsString::Split(Line, Separator);
		TransferLogRecord.DateTime = TransferLogDataLine[0];
		TransferLogRecord.SourceClientAccountNumber = TransferLogDataLine[1];
		TransferLogRecord.DestinationClientAccountNumber = TransferLogDataLine[2];
		TransferLogRecord.Amount = stod(TransferLogDataLine[3]);
		TransferLogRecord.SourceClientBalanceAfter = stod(TransferLogDataLine[4]);
		TransferLogRecord.DestinationClientBalanceAfter = stod(TransferLogDataLine[5]);
		TransferLogRecord.UserName = TransferLogDataLine[6];

		return TransferLogRecord;
	}

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Separator);


		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static clsBankClient _getEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#") {
		string DataLine = "";

		DataLine += Client.FirstName + Separator;
		DataLine += Client.LastName + Separator;
		DataLine += Client.Email + Separator;
		DataLine += Client.Phone + Separator;
		DataLine += Client.getAccountNumber() + Separator;
		DataLine += Client.PinCode + Separator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out); // overwrite mode

		string DataLine;

		if (MyFile.is_open()) {
			for (clsBankClient C : vClients) {
				if (C._MarkedForDeleted == false) {
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update() {
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients) {
			if (C.getAccountNumber() == getAccountNumber()) {
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	void _AddDataLineToFile(string DataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);

		if (MyFile.is_open()) {
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient, string UserName, string Separator = "#//#") {
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::getSystemDateTimeString() + Separator;
		TransferLogRecord += getAccountNumber() + Separator;
		TransferLogRecord += DestinationClient.getAccountNumber() + Separator;
		TransferLogRecord += to_string(Amount) + Separator;
		TransferLogRecord += to_string(AccountBalance) + Separator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Separator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName) {
		string DataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord {
		string DateTime;
		string SourceClientAccountNumber;
		string DestinationClientAccountNumber;
		double Amount;
		double SourceClientBalanceAfter;
		double DestinationClientBalanceAfter;
		string UserName;
	};

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string getAccountNumber() {
		return _AccountNumber;
	}

	void setPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string getPinCode() {
		return _PinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	float getAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	/*
	// No UI related code inside object!
	void Print() {
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << getFirstName();
		cout << "\nLastName    : " << getLastName();
		cout << "\nFull Name   : " << getFullName();
		cout << "\nEmail       : " << getEmail();
		cout << "\nPhone       : " << getPhone();
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";
	}
	*/

	static clsBankClient Find(string AccountNumber) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.getAccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _getEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.getAccountNumber() == AccountNumber && Client.getPinCode() == PinCode) {
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _getEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };

	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResults::svFailedAccountNumberExists;
			}
			_AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSucceeded;
		}
	}

	static clsBankClient getAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients) {
			if (C.getAccountNumber() == _AccountNumber) {
				C._MarkedForDeleted = true;
				_SaveClientsDataToFile(vClients);
				*this = _getEmptyClientObject();
				return true;
			}
		}

		return false;
	}

	static vector <clsBankClient> getClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double getTotalBalances() {
		vector <clsBankClient> vClients = getClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients) {
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName) {
		if (Amount > AccountBalance) {
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}

	static vector <stTransferLogRecord> getTransferLogList() {
		vector <stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line)) {
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferLogRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}
};