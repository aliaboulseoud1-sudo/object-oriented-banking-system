#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsCurrency {
private:
	enum _enMode { EmptyMode = 0, UpdateMode = 1 };
	_enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#") {
		vector <string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Separator);

		return clsCurrency(_enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#") {
		string CurrencyRecord = "";

		CurrencyRecord += Currency.getCountry() + Separator;
		CurrencyRecord += Currency.getCurrencyCode() + Separator;
		CurrencyRecord += Currency.getCurrencyName() + Separator;
		CurrencyRecord += to_string(Currency.getRate());

		return CurrencyRecord;
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {
		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (MyFile.is_open()) {
			for (clsCurrency C : vCurrencies) {
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update() {
		vector <clsCurrency> vCurrencies;
		vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : vCurrencies) {
			if (C.getCurrencyCode() == getCurrencyCode()) {
				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencies);
	}

	static clsCurrency _getEmptyCurrencyObject() {
		return clsCurrency(_enMode::EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(_enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static vector <clsCurrency> getAllUSDRates() {
		return _LoadCurrenciesDataFromFile();
	}

	bool IsEmpty() {
		return (_Mode == _enMode::EmptyMode);
	}

	string getCountry() {
		return _Country;
	}

	string getCurrencyCode() {
		return _CurrencyCode;
	}

	string getCurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	float getRate() {
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.getCurrencyCode() == CurrencyCode) {
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _getEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.getCountry()) == Country) {
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _getEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> getCurrenciesList() {
		return _LoadCurrenciesDataFromFile();
	}

	double ConvertToUSD(double Amount) {
		return (Amount / getRate());
	}

	double ConvertToOtherCurrency(double Amount, clsCurrency Currency2) {
		double AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.getCurrencyCode() == "USD") {
			return AmountInUSD;
		}

		return (AmountInUSD * Currency2.getRate());
	}
};

