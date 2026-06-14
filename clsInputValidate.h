/*#pragma once

#include <iostream>
#include "clsDate.h"
#include "clsUtil.h"
#include <string>
using namespace std;

class clsInputValidate {
public:
	static bool IsNumberBetween(int number, int from, int to) {
		if (from > to) clsUtil::Swap(from, to);
		return (number >= from && number <= to);
	}

	static bool IsNumberBetween(double number, double from, double to) {
		if (from > to) clsUtil::Swap(from, to);
		return (number >= from && number <= to);
	}

	static bool IsNumberBetween(float number, float from, float to) {
		if (from > to) swap(from, to);
		return (number >= from && number <= to);
	}

	static bool IsNumberBetween(short number, short from, short to) {
		if (from > to) swap(from, to);
		return (number >= from && number <= to);
	}

	static bool IsDateBetween(clsDate Date, clsDate Date1, clsDate Date2) {
		if (clsDate::IsDate1AfterDate2(Date1, Date2)) {
			clsDate::SwapDates(Date1, Date2);
		}

		return (
			(clsDate::IsDate1EqualToDate2(Date, Date1) || clsDate::IsDate1AfterDate2(Date, Date1)) &&
			(clsDate::IsDate1EqualToDate2(Date, Date2) || clsDate::IsDate1LessThanDate2(Date, Date2))
			);
	}

	static int ReadIntNumber(string message) {
		int number;

		while (!(cin >> number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << message << endl;
		}

		return number;
	}

	static int ReadIntNumberBetween(int from, int to, string message) {
		int number;

		number = ReadIntNumber("Invalid Number, Enter again:\n");

		while (!IsNumberBetween(number, from ,to)) {
			cout << message << endl;
			number = ReadIntNumber("Invalid Number, Enter again:\n");
		}

		return number;
	}

	static double ReadDblNumber(string message) {
		double number;

		while (!(cin >> number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << message << endl;
		}

		return number;
	}

	static double ReadDblNumberBetween(double from, double to, string message) {
		double number;

		number = ReadDblNumber("Invalid Number, Enter again:\n");

		while (!IsNumberBetween(number, from, to)) {
			cout << message << endl;
			number = ReadDblNumber("Invalid Number, Enter again:\n");
		}

		return number;
	}

	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}
}; */







#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"


class clsInputValidate {
public:
	template <typename T>
	static bool IsNumberBetween(T Number, T From, T To) {
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {
		if (clsDate::IsDate1AfterDate2(From, To)) {
			clsDate::SwapDates(From, To);
		}

		return (
			(clsDate::IsDate1EqualToDate2(Date, From) || clsDate::IsDate1AfterDate2(Date, From)) &&
			(clsDate::IsDate1EqualToDate2(Date, To) || clsDate::IsDate1LessThanDate2(Date, To))
			);
	}

	template <typename T>
	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again:\n") {
		T Number;

		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
		}

		return Number;
	}

	template <typename T>
	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, enter again:\n") {
		T Number;

		Number = ReadNumber<T>();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadNumber<T>();
		}

		return Number;
	}

	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}

	static string ReadString() {
		string str = "";
		getline(cin >> ws, str);
		return str;
	}
};