#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;

class clsTransferLogScreen : protected clsScreen {
private:
	static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord) {
		cout << setw(8) << left << "" << "| " << setw(26) << left << TransferLogRecord.DateTime;
		cout << "| " << setw(10) << left << TransferLogRecord.SourceClientAccountNumber;
		cout << "| " << setw(10) << left << TransferLogRecord.DestinationClientAccountNumber;
		cout << "| " << setw(22) << left << to_string(TransferLogRecord.Amount);
		cout << "| " << setw(22) << left << to_string(TransferLogRecord.SourceClientBalanceAfter);
		cout << "| " << setw(22) << left << to_string(TransferLogRecord.DestinationClientBalanceAfter);
		cout << "| " << setw(10) << left << TransferLogRecord.UserName;
	}

public:
	static void ShowTransferLogScreen() {
		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::getTransferLogList();

		string Title = "\t Transfer Log List Screen";
		string SubTitle = "\t\t(" + to_string(vTransferLogRecord.size()) + ") Record(s).";

		__DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(26) << "Date/Time";
		cout << "| " << left << setw(10) << "s. Acct";
		cout << "| " << left << setw(10) << "d. Acct";
		cout << "| " << left << setw(22) << "Amount";
		cout << "| " << left << setw(22) << "s. Balance";
		cout << "| " << left << setw(22) << "d. Balance";
		cout << "| " << left << setw(10) << "User";

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vTransferLogRecord.size() == 0) {
			cout << "\t\t\t\tNo Transfer Operations Available In the System!";
		}
		else {
			for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord) {
				_PrintTransferLogRecordLine(Record);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

