/*//             ************** MY SOLUTION **************


#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsDate {
private:
	short _Day;
	short _Month;
	int _Year;

public:
	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string Date) {
		vector <string> vDate;
		vDate = clsString::Split(Date, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, int Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short NumberOfDaysFromBeginning, int Year) {
		_Year = Year;
		_Month = 1;

		while (NumberOfDaysFromBeginning > NumberOfDaysInMonth(Year, _Month)) {
			NumberOfDaysFromBeginning -= NumberOfDaysInMonth(Year, _Month);
			_Month++;
		}

		_Day = NumberOfDaysFromBeginning;
	}

	void setDay(short Day) {
		_Day = Day;
	}

	short getDay() {
		return _Day;
	}

	void setMonth(short Month) {
		_Month = Month;
	}

	short getMonth() {
		return _Month;
	}

	void setYear(int Year) {
		_Year = Year;
	}

	int getYear() {
		return _Year;
	}

	static bool IsLeapYear(short Year) {
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Year, short Month) {
		if (Month < 1 || Month > 12) return 0;
		short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}

	short NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static clsDate GetDateFromDayOrderInYear(short Year, short NumberOfDaysFromBeginning) {
		clsDate Date;

		Date._Year = Year;
		Date._Month = 1;

		while (NumberOfDaysFromBeginning > NumberOfDaysInMonth(Year, Date._Month)) {
			NumberOfDaysFromBeginning -= NumberOfDaysInMonth(Year, Date._Month);
			Date._Month++;
		}

		Date._Day = NumberOfDaysFromBeginning;
		return Date;
	}

	clsDate GetDateFromDayOrderInYear(short NumberOfDaysFromBeginning) {
		return GetDateFromDayOrderInYear(_Year, NumberOfDaysFromBeginning);
	}

	static string DateToString(clsDate Date) {
		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}

	string DateToString() {
		return DateToString(*this);
	}

	void Print() {
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	static short NumberOfDaysInAYear(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear() {
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year) {
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear() {
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year) {
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear() {
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year) {
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear() {
		return NumberOfSecondsInAYear(_Year);
	}

	static short CalculateNumberOfDaysFromBeginningOFYear(short Year, short Month, short Day) {
		short NumberOfDaysFromBeginning = Day;

		for (short i = 1; i < Month; i++) {
			NumberOfDaysFromBeginning += NumberOfDaysInMonth(Year, i);
		}

		return NumberOfDaysFromBeginning;
	}

	short CalculateNumberOfDaysFromBeginningOFYear() {
		return CalculateNumberOfDaysFromBeginningOFYear(_Year, _Month, _Day);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return (NumberOfDaysInMonth(Date._Year, Date._Month) == Date._Day);
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {
		return (Month == 12);
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate Date) {
		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date._Month)) {
				Date._Year++;
				Date._Day = 1;
				Date._Month = 1;
			}
			else {
				Date._Month++;
				Date._Day = 1;
			}
		}

		else {
			Date._Day++;
		}

		return Date;
	}

	clsDate AddOneDay() {
		return AddOneDay(*this);
	}

	static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2) {
		return (Date1._Day == Date2._Day && Date1._Month == Date2._Month && Date1._Year == Date2._Year);
	}

	bool IsDate1EqualToDate2(clsDate Date2) {
		return IsDate1EqualToDate2(*this, Date2);
	}

	static bool IsDate1LessThanDate2(clsDate Date1, clsDate Date2) {

		if (Date1._Year < Date2._Year) {
			return true;
		}
		else if (Date1._Year == Date2._Year) {
			if (Date1._Month < Date2._Month) {
				return true;
			}
			else if (Date1._Month == Date2._Month) {
				return Date1._Day < Date2._Day;
			}
		}

		return false;
	}

	bool IsDate1LessThanDate2(clsDate Date2) {
		return IsDate1LessThanDate2(*this, Date2);
	}

	static short CalculateDifferenceBetweenTwoDatesInDays(clsDate Date1, clsDate Date2, bool DiffIncludingEndDay = false) {
		short DiffInDays = 0;

		if (IsDate1EqualToDate2(Date1, Date2)) {
			return DiffInDays;
		}

		if (IsDate1LessThanDate2(Date1, Date2)) {
			swap(Date1, Date2);
		}

		while (!IsDate1EqualToDate2(Date1, Date2)) {
			Date2 = AddOneDay(Date2);
			DiffInDays++;
		}

		if (DiffIncludingEndDay == true) {
			DiffInDays++;
		}

		return DiffInDays;
	}

	short CalculateDifferenceBetweenTwoDatesInDays(clsDate Date2, bool DiffIncludingEndDay = false) {
		return CalculateDifferenceBetweenTwoDatesInDays(*this, Date2, DiffIncludingEndDay);
	}

	static clsDate GetSystemDate() {
		clsDate SystemDate;

		time_t now = time(0);
		tm* ltm = localtime(&now);

		SystemDate._Day = ltm->tm_mday;
		SystemDate._Month = ltm->tm_mon + 1;
		SystemDate._Year = ltm->tm_year + 1900;

		return SystemDate;
	}

	static short CalculateAgeInDays(clsDate BirthDate) {
		short AgeInDays;
		clsDate CurrentDate;

		CurrentDate = GetSystemDate();
		AgeInDays = CalculateDifferenceBetweenTwoDatesInDays(CurrentDate, BirthDate);

		return AgeInDays;
	}

	short CalculateAgeInDays() {
		return CalculateAgeInDays(*this);
	}

	static short NumberOfHoursInMonth(short Year, short Month) {
		return NumberOfDaysInMonth(Year, Month) * 24;
	}

	short NumberOfHoursInMonth() {
		return NumberOfHoursInMonth(_Year, _Month);
	}

	static int NumberOfMinutesInMonth(short Year, short Month) {
		return NumberOfHoursInMonth(Year, Month) * 60;
	}

	int NumberOfMinutesInMonth() {
		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month) {
		return NumberOfMinutesInMonth(Year, Month) * 60;
	}

	int NumberOfSecondsInMonth() {
		return NumberOfSecondsInMonth(_Year, _Month);
	}

	static short DefineDayOrder(short Year, short Month, short Day) {
		short a, y, m, d;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;


		d = (Day + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;

		return d;
	}

	short DefineDayOrder() {
		return DefineDayOrder(_Year, _Month, _Day);
	}

	static string DefineDayName(short d) {
		string WeekDays[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		return WeekDays[d];
	}

	static string MonthName(short Month) {
		string MonthsName[12] = { "Jan", "Feb", "Mar", "Apr",
			"May", "Jun", "Jul", "Aug",
			"Sep", "Oct", "Nov", "Dec"
		};

		return MonthsName[Month - 1];
	}

	string MonthName() {
		return MonthName(_Month);
	}

	static void PrintMonthCalendar(short Year, short Month) {

		short DayOrder = DefineDayOrder(Year, Month, 1);
		short NumberOfDaysInEnteredMonth = NumberOfDaysInMonth(Year, Month);

		printf("\n  _______________%s_______________\n\n", MonthName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;
		for (i = 0; i < DayOrder; i++) {
			printf("     ");
		}

		for (short day = 1; day <= NumberOfDaysInEnteredMonth; day++) {
			printf("%5d", day);

			if (++i == 7) {
				i = 0;
				printf("\n");
			}
		}

		printf("\n  ________________________________\n\n");
	}

	void PrintMonthCalendar() {
		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short Year) {
		printf("\n  ________________________________");
		printf("\n\n         Calendar - %d", Year);
		printf("\n  ________________________________\n\n");

		for (short Month = 1; Month <= 12; Month++) {
			PrintMonthCalendar(Year, Month);
		}
	}

	void PrintYearCalendar() {
		PrintYearCalendar(_Year);
	}

	static clsDate AddDaysToDate(short DaysToAdd, clsDate Date) {
		short RemainingDays = DaysToAdd + CalculateNumberOfDaysFromBeginningOFYear(Date._Year, Date._Month, Date._Day);
		short MonthDays = 0;

		Date._Month = 1;
		while (true) {
			MonthDays = NumberOfDaysInMonth(Date._Year, Date._Month);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Date._Month++;

				if (Date._Month > 12) {
					Date._Month = 1;
					Date._Year++;
				}
			}

			else {
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	clsDate AddDaysToDate(short DaysToAdd) {
		return AddDaysToDate(DaysToAdd, *this);
	}

	static clsDate IncreaseDateByXDays(clsDate Date, int XDays) {
		for (int i = 0; i < XDays; i++) {
			Date = AddOneDay(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXDays(int XDays) {
		return IncreaseDateByXDays(*this, XDays);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date) {
		for (int i = 0; i < 7; i++) {
			Date = AddOneDay(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByOneWeek() {
		return IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, int XWeeks) {
		for (int i = 0; i < XWeeks; i++) {
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXWeeks(int XWeeks) {
		return IncreaseDateByXWeeks(*this, XWeeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date) {
		if (Date._Month == 12) {
			Date._Year++;
			Date._Month = 1;
		}
		else {
			Date._Month++;
		}

		short DaysInNewMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

		if (Date._Day > DaysInNewMonth) {
			Date._Day = DaysInNewMonth;
		}

		return Date;
	}

	clsDate IncreaseDateByOneMonth() {
		return IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, int XMonths) {
		for (int i = 0; i < XMonths; i++) {
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXMonths(int XMonths) {
		return IncreaseDateByXMonths(*this, XMonths);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date) {
		return IncreaseDateByXMonths(Date, 12);
	}

	clsDate IncreaseDateByOneYear() {
		return IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate Date, int XYears) {
		short OriginalDay = Date._Day;

		for (int i = 0; i < XYears; i++) {
			Date._Year++;
			short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
			Date._Day = min(OriginalDay, MaxDay);
		}

		return Date;
	}

	clsDate IncreaseDateByXYears(int XYears) {
		return IncreaseDateByXYears(*this, XYears);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate Date, int XYears) {
		short OriginalDay = Date._Day;

		Date._Year += XYears;

		short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDay);

		return Date;
	}

	clsDate IncreaseDateByXYearsFaster(int XYears) {
		return IncreaseDateByXYearsFaster(*this, XYears);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date) {
		return IncreaseDateByXYearsFaster(Date, 10);
	}

	clsDate IncreaseDateByOneDecade() {
		return IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate Date, int XDecades) {
		for (int i = 0; i < XDecades; i++) {
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXDecades(int XDecades) {
		return IncreaseDateByXDecades(*this, XDecades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate Date, int XDecades) {
		short OriginalDay = Date._Day;

		Date._Year += 10 * XDecades;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	clsDate IncreaseDateByXDecadesFaster(int XDecades) {
		return IncreaseDateByXDecadesFaster(*this, XDecades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date) {
		short OriginalDay = Date._Day;

		Date._Year += 100;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	clsDate IncreaseDateByOneCentury() {
		return IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date) {
		short OriginalDay = Date._Day;

		Date._Year += 1000;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	clsDate IncreaseDateByOneMillennium() {
		return IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date) {
		if (Date._Day == 1) {
			if (Date._Month == 1) {
				Date._Year--;
				Date._Month = 12;
				Date._Day = 31;
			}
			else {
				Date._Month--;
				Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
			}
		}

		else {
			Date._Day--;
		}

		return Date;
	}

	clsDate DecreaseDateByOneDay() {
		return DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate Date, int XDays) {
		for (int i = 0; i < XDays; i++) {
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXDays(int XDays) {
		return DecreaseDateByXDays(*this, XDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date) {
		for (int i = 0; i < 7; i++) {
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByOneWeek() {
		return DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, int XWeeks) {
		for (int i = 0; i < XWeeks; i++) {
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXWeeks(int XWeeks) {
		return DecreaseDateByXWeeks(*this, XWeeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date) {
		if (Date._Month == 1) {
			Date._Year--;
			Date._Month = 12;
		}
		else {
			Date._Month--;
		}

		short DaysInNewMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

		if (Date._Day > DaysInNewMonth) {
			Date._Day = DaysInNewMonth;
		}

		return Date;
	}

	clsDate DecreaseDateByOneMonth() {
		return DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, int XMonths) {
		for (int i = 0; i < XMonths; i++) {
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXMonths(int XMonths) {
		return DecreaseDateByXMonths(*this, XMonths);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date) {
		return DecreaseDateByXMonths(Date, 12);
	}

	clsDate DecreaseDateByOneYear() {
		return DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate Date, int XYears) {
		short OriginalDay = Date._Day;

		for (int i = 0; i < XYears; i++) {
			Date._Year--;
			short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
			Date._Day = min(OriginalDay, MaxDay);
		}

		return Date;
	}

	clsDate DecreaseDateByXYears(int XYears) {
		return DecreaseDateByXYears(*this, XYears);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate Date, int XYears) {
		short OriginalDay = Date._Day;

		Date._Year -= XYears;

		short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDay);

		return Date;
	}

	clsDate DecreaseDateByXYearsFaster(int XYears) {
		return DecreaseDateByXYearsFaster(*this, XYears);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date) {
		return DecreaseDateByXYearsFaster(Date, 10);
	}

	clsDate DecreaseDateByOneDecade() {
		return DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, int XDecades) {
		for (int i = 0; i < XDecades; i++) {
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXDecades(int XDecades) {
		return DecreaseDateByXDecades(*this, XDecades);
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate Date, int XDecades) {
		short OriginalDay = Date._Day;

		Date._Year -= 10 * XDecades;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	clsDate DecreaseDateByXDecadesFaster(int XDecades) {
		return DecreaseDateByXDecadesFaster(*this, XDecades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date) {
		short OriginalDay = Date._Day;

		Date._Year -= 100;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	clsDate DecreaseDateByOneCentury() {
		return DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date) {
		short OriginalDay = Date._Day;

		Date._Year -= 1000;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	clsDate DecreaseDateByOneMillennium() {
		return DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(short DayIndexInWeek) {
		return (DayIndexInWeek == 6);
	}

	static bool IsWeekEnd(short DayIndexInWeek) {
		return (DayIndexInWeek == 6 || DayIndexInWeek == 5);
	}

	static bool IsBusinessDay(short DayIndexInWeek) {
		return !IsWeekEnd(DayIndexInWeek);
	}

	static short DaysUntilTheEndOfWeek(short DayIndexInWeek) {
		return (6 - DayIndexInWeek);
	}

	static short DaysUntilTheEndOfMonth(clsDate CurrentDate) {
		clsDate EndOfMonthDate;
		EndOfMonthDate._Day = NumberOfDaysInMonth(CurrentDate._Year, CurrentDate._Month);
		EndOfMonthDate._Month = CurrentDate._Month;
		EndOfMonthDate._Year = CurrentDate._Year;

		return CalculateDifferenceBetweenTwoDatesInDays(CurrentDate, EndOfMonthDate, true);
	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate DateOfEndOfYear, clsDate CurrentDate) {
		DateOfEndOfYear._Day = 31;
		DateOfEndOfYear._Month = 12;
		DateOfEndOfYear._Year = CurrentDate._Year;

		return CalculateDifferenceBetweenTwoDatesInDays(CurrentDate, DateOfEndOfYear, true);
	}

	short DaysUntilTheEndOfYear(clsDate DateOfEndOfYear) {
		return DaysUntilTheEndOfYear(DateOfEndOfYear, *this);
	}

	static short DayOfWeekOrder(short Year, short Month, short Day) {
		short a, y, m, d;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;


		d = (Day + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;

		return d;
	}

	static short DayOfWeekOrder(clsDate Date) {
		return DayOfWeekOrder(Date._Year, Date._Month, Date._Day);
	}

	static short CalculateActualVacationDays(clsDate DateVacationStarting, clsDate DateVacationEnding) {
		short DaysCount = 0;

		while (IsDate1LessThanDate2(DateVacationStarting, DateVacationEnding)) {
			if (IsBusinessDay(DayOfWeekOrder(DateVacationStarting))) {
				DaysCount++;
			}

			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		return DaysCount;
	}

	short CalculateActualVacationDays(clsDate DateVacationEnding) {
		return CalculateActualVacationDays(*this, DateVacationEnding);
	}

	static clsDate ReturnDateFromVacation(clsDate DateVacationStarting, short VacationDays) {
		short WeekEndCounter = 0;

		while (IsWeekEnd(DayOfWeekOrder(DateVacationStarting))) {
			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		for (short i = 0; i < VacationDays + WeekEndCounter; i++) {
			if (IsWeekEnd(DayOfWeekOrder(DateVacationStarting))) {
				WeekEndCounter++;
			}

			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		while (IsWeekEnd(DayOfWeekOrder(DateVacationStarting))) {
			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		return DateVacationStarting;
	}

	clsDate ReturnDateFromVacation(short VacationDays) {
		return ReturnDateFromVacation(*this, VacationDays);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
		return (!IsDate1LessThanDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2));
	}

	bool IsDate1AfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enCompareTwoDates {
		Before = -1,
		Equal = 0,
		After = 1
	};

	static enCompareTwoDates CompareTwoDates(clsDate Date1, clsDate Date2) {
		if (IsDate1AfterDate2(Date1, Date2)) {
			return enCompareTwoDates::After;
		}
		else if (IsDate1LessThanDate2(Date1, Date2)) {
			return enCompareTwoDates::Before;
		}
		else {
			return enCompareTwoDates::Equal;
		}
	}

	enCompareTwoDates CompareTwoDates(clsDate Date2) {
		return CompareTwoDates(*this, Date2);
	}

	static bool IsValidDate(clsDate Date) {
		return (Date._Day <= NumberOfDaysInMonth(Date._Year, Date._Month) && Date._Day >= 1)
			&& (Date._Month >= 1 && Date._Month <= 12)
			&& (Date._Year >= 1);
	}

	bool IsValidDate() {
		return IsValidDate(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2) {
		clsDate TempDate;

		TempDate._Year = Date1._Year;
		TempDate._Month = Date1._Month;
		TempDate._Day = Date1._Day;

		Date1._Year = Date2._Year;
		Date1._Month = Date2._Month;
		Date1._Day = Date2._Day;

		Date2._Year = TempDate._Year;
		Date2._Month = TempDate._Month;
		Date2._Day = TempDate._Day;
	}

	void SwapDates(clsDate& Date2) {
		return SwapDates(*this, Date2);
	}
};*/










#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate {
private:
	short _Day;
	short _Month;
	int _Year;

public:
	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string Date) {
		vector <string> vDate;
		vDate = clsString::Split(Date, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, int Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrderInYear, int Year) {
		clsDate Date = GetDateFromDayOrderInYear(Year, DayOrderInYear);

		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}

	void setDay(short Day) {
		_Day = Day;
	}

	short getDay() {
		return _Day;
	}

	void setMonth(short Month) {
		_Month = Month;
	}

	short getMonth() {
		return _Month;
	}

	void setYear(int Year) {
		_Year = Year;
	}

	int getYear() {
		return _Year;
	}

	static bool IsLeapYear(short Year) {
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Year, short Month) {
		if (Month < 1 || Month > 12) return 0;
		short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}

	short NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static clsDate GetDateFromDayOrderInYear(short Year, short NumberOfDaysFromBeginning) {
		clsDate Date;

		Date._Year = Year;
		Date._Month = 1;

		while (NumberOfDaysFromBeginning > NumberOfDaysInMonth(Year, Date._Month)) {
			NumberOfDaysFromBeginning -= NumberOfDaysInMonth(Year, Date._Month);
			Date._Month++;
		}

		Date._Day = NumberOfDaysFromBeginning;
		return Date;
	}

	clsDate GetDateFromDayOrderInYear(short NumberOfDaysFromBeginning) {
		return GetDateFromDayOrderInYear(_Year, NumberOfDaysFromBeginning);
	}

	static string DateToString(clsDate Date) {
		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}

	string DateToString() {
		return DateToString(*this);
	}

	void Print() {
		cout << DateToString() << endl;
	}

	static short NumberOfDaysInAYear(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear() {
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year) {
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear() {
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year) {
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear() {
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year) {
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear() {
		return NumberOfSecondsInAYear(_Year);
	}

	static short CalculateNumberOfDaysFromBeginningOFYear(short Year, short Month, short Day) {
		short NumberOfDaysFromBeginning = Day;

		for (short i = 1; i < Month; i++) {
			NumberOfDaysFromBeginning += NumberOfDaysInMonth(Year, i);
		}

		return NumberOfDaysFromBeginning;
	}

	short CalculateNumberOfDaysFromBeginningOFYear() {
		return CalculateNumberOfDaysFromBeginningOFYear(_Year, _Month, _Day);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return (NumberOfDaysInMonth(Date._Year, Date._Month) == Date._Day);
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {
		return (Month == 12);
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate Date) {
		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date._Month)) {
				Date._Year++;
				Date._Day = 1;
				Date._Month = 1;
			}
			else {
				Date._Month++;
				Date._Day = 1;
			}
		}

		else {
			Date._Day++;
		}

		return Date;
	}

	clsDate AddOneDay() {
		return AddOneDay(*this);
	}

	static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2) {
		return (Date1._Day == Date2._Day && Date1._Month == Date2._Month && Date1._Year == Date2._Year);
	}

	bool IsDate1EqualToDate2(clsDate Date2) {
		return IsDate1EqualToDate2(*this, Date2);
	}

	static bool IsDate1LessThanDate2(clsDate Date1, clsDate Date2) {

		if (Date1._Year < Date2._Year) {
			return true;
		}
		else if (Date1._Year == Date2._Year) {
			if (Date1._Month < Date2._Month) {
				return true;
			}
			else if (Date1._Month == Date2._Month) {
				return Date1._Day < Date2._Day;
			}
		}

		return false;
	}

	bool IsDate1LessThanDate2(clsDate Date2) {
		return IsDate1LessThanDate2(*this, Date2);
	}

	static short CalculateDifferenceBetweenTwoDatesInDays(clsDate Date1, clsDate Date2, bool DiffIncludingEndDay = false) {
		short DiffInDays = 0;

		if (IsDate1EqualToDate2(Date1, Date2)) {
			return DiffInDays;
		}

		if (IsDate1LessThanDate2(Date1, Date2)) {
			swap(Date1, Date2);
		}

		while (!IsDate1EqualToDate2(Date1, Date2)) {
			Date2 = AddOneDay(Date2);
			DiffInDays++;
		}

		if (DiffIncludingEndDay == true) {
			DiffInDays++;
		}

		return DiffInDays;
	}

	short CalculateDifferenceBetweenTwoDatesInDays(clsDate Date2, bool DiffIncludingEndDay = false) {
		return CalculateDifferenceBetweenTwoDatesInDays(*this, Date2, DiffIncludingEndDay);
	}

	static clsDate GetSystemDate() {
		clsDate SystemDate;

		time_t now = time(0);
		tm* ltm = localtime(&now);

		SystemDate._Day = ltm->tm_mday;
		SystemDate._Month = ltm->tm_mon + 1;
		SystemDate._Year = ltm->tm_year + 1900;

		return SystemDate;
	}

	static short CalculateAgeInDays(clsDate BirthDate) {
		short AgeInDays;
		clsDate CurrentDate;

		CurrentDate = GetSystemDate();
		AgeInDays = CalculateDifferenceBetweenTwoDatesInDays(CurrentDate, BirthDate);

		return AgeInDays;
	}

	static short NumberOfHoursInMonth(short Year, short Month) {
		return NumberOfDaysInMonth(Year, Month) * 24;
	}

	short NumberOfHoursInMonth() {
		return NumberOfHoursInMonth(_Year, _Month);
	}

	static int NumberOfMinutesInMonth(short Year, short Month) {
		return NumberOfHoursInMonth(Year, Month) * 60;
	}

	int NumberOfMinutesInMonth() {
		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month) {
		return NumberOfMinutesInMonth(Year, Month) * 60;
	}

	int NumberOfSecondsInMonth() {
		return NumberOfSecondsInMonth(_Year, _Month);
	}

	static short DefineDayOrder(short Year, short Month, short Day) {
		short a, y, m, d;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;


		d = (Day + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;

		return d;
	}

	short DefineDayOrder() {
		return DefineDayOrder(_Year, _Month, _Day);
	}

	static string DefineDayName(short d) {
		string WeekDays[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		return WeekDays[d];
	}

	static string MonthName(short Month) {
		string MonthsName[12] = { "Jan", "Feb", "Mar", "Apr",
			"May", "Jun", "Jul", "Aug",
			"Sep", "Oct", "Nov", "Dec"
		};

		return MonthsName[Month - 1];
	}

	string MonthName() {
		return MonthName(_Month);
	}

	static void PrintMonthCalendar(short Year, short Month) {

		short DayOrder = DefineDayOrder(Year, Month, 1);
		short NumberOfDaysInEnteredMonth = NumberOfDaysInMonth(Year, Month);

		printf("\n  _______________%s_______________\n\n", MonthName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;
		for (i = 0; i < DayOrder; i++) {
			printf("     ");
		}

		for (short day = 1; day <= NumberOfDaysInEnteredMonth; day++) {
			printf("%5d", day);

			if (++i == 7) {
				i = 0;
				printf("\n");
			}
		}

		printf("\n  ________________________________\n\n");
	}

	void PrintMonthCalendar() {
		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short Year) {
		printf("\n  ________________________________");
		printf("\n\n         Calendar - %d", Year);
		printf("\n  ________________________________\n\n");

		for (short Month = 1; Month <= 12; Month++) {
			PrintMonthCalendar(Year, Month);
		}
	}

	void PrintYearCalendar() {
		PrintYearCalendar(_Year);
	}

	static clsDate AddDaysToDate(short DaysToAdd, clsDate Date) {
		short RemainingDays = DaysToAdd + CalculateNumberOfDaysFromBeginningOFYear(Date._Year, Date._Month, Date._Day);
		short MonthDays = 0;

		Date._Month = 1;
		while (true) {
			MonthDays = NumberOfDaysInMonth(Date._Year, Date._Month);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Date._Month++;

				if (Date._Month > 12) {
					Date._Month = 1;
					Date._Year++;
				}
			}

			else {
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	clsDate AddDaysToDate(short DaysToAdd) {
		return AddDaysToDate(DaysToAdd, *this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, int XDays) {
		for (int i = 0; i < XDays; i++) {
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(int XDays) {
		IncreaseDateByXDays(*this, XDays);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date) {
		for (int i = 0; i < 7; i++) {
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, int XWeeks) {
		for (int i = 0; i < XWeeks; i++) {
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void IncreaseDateByXWeeks(int XWeeks) {
		IncreaseDateByXWeeks(*this, XWeeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date) {
		if (Date._Month == 12) {
			Date._Year++;
			Date._Month = 1;
		}
		else {
			Date._Month++;
		}

		short DaysInNewMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

		if (Date._Day > DaysInNewMonth) {
			Date._Day = DaysInNewMonth;
		}

		return Date;
	}

	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, int XMonths) {
		for (int i = 0; i < XMonths; i++) {
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(int XMonths) {
		IncreaseDateByXMonths(*this, XMonths);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {
		return IncreaseDateByXMonths(Date, 12);
	}

	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, int XYears) {
		short OriginalDay = Date._Day;

		for (int i = 0; i < XYears; i++) {
			Date._Year++;
			short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
			Date._Day = min(OriginalDay, MaxDay);
		}

		return Date;
	}

	void IncreaseDateByXYears(int XYears) {
		IncreaseDateByXYears(*this, XYears);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate& Date, int XYears) {
		short OriginalDay = Date._Day;

		Date._Year += XYears;

		short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDay);

		return Date;
	}

	void IncreaseDateByXYearsFaster(int XYears) {
		IncreaseDateByXYearsFaster(*this, XYears);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {
		IncreaseDateByXYearsFaster(Date, 10);
	}

	void IncreaseDateByOneDecade() {
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, int XDecades) {
		for (int i = 0; i < XDecades; i++) {
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void IncreaseDateByXDecades(int XDecades) {
		IncreaseDateByXDecades(*this, XDecades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate& Date, int XDecades) {
		short OriginalDay = Date._Day;

		Date._Year += 10 * XDecades;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	void IncreaseDateByXDecadesFaster(int XDecades) {
		IncreaseDateByXDecadesFaster(*this, XDecades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {
		short OriginalDay = Date._Day;

		Date._Year += 100;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date) {
		short OriginalDay = Date._Day;

		Date._Year += 1000;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date) {
		if (Date._Day == 1) {
			if (Date._Month == 1) {
				Date._Year--;
				Date._Month = 12;
				Date._Day = 31;
			}
			else {
				Date._Month--;
				Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
			}
		}

		else {
			Date._Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay() {
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, int XDays) {
		for (int i = 0; i < XDays; i++) {
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByXDays(int XDays) {
		DecreaseDateByXDays(*this, XDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {
		for (int i = 0; i < 7; i++) {
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek() {
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, int XWeeks) {
		for (int i = 0; i < XWeeks; i++) {
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeeks(int XWeeks) {
		DecreaseDateByXWeeks(*this, XWeeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {
		if (Date._Month == 1) {
			Date._Year--;
			Date._Month = 12;
		}
		else {
			Date._Month--;
		}

		short DaysInNewMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

		if (Date._Day > DaysInNewMonth) {
			Date._Day = DaysInNewMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, int XMonths) {
		for (int i = 0; i < XMonths; i++) {
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonths(int XMonths) {
		DecreaseDateByXMonths(*this, XMonths);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {
		return DecreaseDateByXMonths(Date, 12);
	}

	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, int XYears) {
		short OriginalDay = Date._Day;

		for (int i = 0; i < XYears; i++) {
			Date._Year--;
			short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
			Date._Day = min(OriginalDay, MaxDay);
		}

		return Date;
	}

	void DecreaseDateByXYears(int XYears) {
		DecreaseDateByXYears(*this, XYears);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate& Date, int XYears) {
		short OriginalDay = Date._Day;

		Date._Year -= XYears;

		short MaxDay = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDay);

		return Date;
	}

	void DecreaseDateByXYearsFaster(int XYears) {
		DecreaseDateByXYearsFaster(*this, XYears);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {
		return DecreaseDateByXYearsFaster(Date, 10);
	}

	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, int XDecades) {
		for (int i = 0; i < XDecades; i++) {
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void DecreaseDateByXDecades(int XDecades) {
		DecreaseDateByXDecades(*this, XDecades);
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate& Date, int XDecades) {
		short OriginalDay = Date._Day;

		Date._Year -= 10 * XDecades;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	void DecreaseDateByXDecadesFaster(int XDecades) {
		DecreaseDateByXDecadesFaster(*this, XDecades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {
		short OriginalDay = Date._Day;

		Date._Year -= 100;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {
		short OriginalDay = Date._Day;

		Date._Year -= 1000;
		short MaxDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = min(OriginalDay, MaxDays);

		return Date;
	}

	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(short DayIndexInWeek) {
		return (DayIndexInWeek == 6);
	}

	static bool IsWeekEnd(short DayIndexInWeek) {
		return (DayIndexInWeek == 6 || DayIndexInWeek == 5);
	}

	static bool IsBusinessDay(short DayIndexInWeek) {
		return !IsWeekEnd(DayIndexInWeek);
	}

	static short DaysUntilTheEndOfWeek(short DayIndexInWeek) {
		return (6 - DayIndexInWeek);
	}

	static short DaysUntilTheEndOfMonth(clsDate CurrentDate) {
		clsDate EndOfMonthDate;
		EndOfMonthDate._Day = NumberOfDaysInMonth(CurrentDate._Year, CurrentDate._Month);
		EndOfMonthDate._Month = CurrentDate._Month;
		EndOfMonthDate._Year = CurrentDate._Year;

		return CalculateDifferenceBetweenTwoDatesInDays(CurrentDate, EndOfMonthDate, true);
	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate DateOfEndOfYear, clsDate CurrentDate) {
		DateOfEndOfYear._Day = 31;
		DateOfEndOfYear._Month = 12;
		DateOfEndOfYear._Year = CurrentDate._Year;

		return CalculateDifferenceBetweenTwoDatesInDays(CurrentDate, DateOfEndOfYear, true);
	}

	short DaysUntilTheEndOfYear(clsDate DateOfEndOfYear) {
		return DaysUntilTheEndOfYear(DateOfEndOfYear, *this);
	}

	static short DayOfWeekOrder(short Year, short Month, short Day) {
		short a, y, m, d;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;


		d = (Day + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;

		return d;
	}

	static short DayOfWeekOrder(clsDate Date) {
		return DayOfWeekOrder(Date._Year, Date._Month, Date._Day);
	}

	static short CalculateBusinessDays(clsDate DateVacationStarting, clsDate DateVacationEnding) {
		short DaysCount = 0;

		while (IsDate1LessThanDate2(DateVacationStarting, DateVacationEnding)) {
			if (IsBusinessDay(DayOfWeekOrder(DateVacationStarting))) {
				DaysCount++;
			}

			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		return DaysCount;
	}

	static short CalculateVacationDays(clsDate DateVacationStarting, clsDate DateVacationEnding) {
		return CalculateBusinessDays(DateVacationStarting, DateVacationEnding);
	}

	static clsDate ReturnDateFromVacation(clsDate DateVacationStarting, short VacationDays) {
		short WeekEndCounter = 0;

		while (IsWeekEnd(DayOfWeekOrder(DateVacationStarting))) {
			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		for (short i = 0; i < VacationDays + WeekEndCounter; i++) {
			if (IsWeekEnd(DayOfWeekOrder(DateVacationStarting))) {
				WeekEndCounter++;
			}

			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		while (IsWeekEnd(DayOfWeekOrder(DateVacationStarting))) {
			DateVacationStarting = AddOneDay(DateVacationStarting);
		}

		return DateVacationStarting;
	}

	clsDate ReturnDateFromVacation(short VacationDays) {
		return ReturnDateFromVacation(*this, VacationDays);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
		return (!IsDate1LessThanDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2));
	}

	bool IsDate1AfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enCompareTwoDates {
		Before = -1,
		Equal = 0,
		After = 1
	};

	static enCompareTwoDates CompareTwoDates(clsDate Date1, clsDate Date2) {
		if (IsDate1AfterDate2(Date1, Date2)) {
			return enCompareTwoDates::After;
		}
		else if (IsDate1LessThanDate2(Date1, Date2)) {
			return enCompareTwoDates::Before;
		}
		else {
			return enCompareTwoDates::Equal;
		}
	}

	enCompareTwoDates CompareTwoDates(clsDate Date2) {
		return CompareTwoDates(*this, Date2);
	}

	static bool IsValidDate(clsDate Date) {
		return (Date._Day <= NumberOfDaysInMonth(Date._Year, Date._Month) && Date._Day >= 1)
			&& (Date._Month >= 1 && Date._Month <= 12)
			&& (Date._Year >= 1);
	}

	bool IsValidDate() {
		return IsValidDate(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2) {
		clsDate TempDate;

		TempDate._Year = Date1._Year;
		TempDate._Month = Date1._Month;
		TempDate._Day = Date1._Day;

		Date1._Year = Date2._Year;
		Date1._Month = Date2._Month;
		Date1._Day = Date2._Day;

		Date2._Year = TempDate._Year;
		Date2._Month = TempDate._Month;
		Date2._Day = TempDate._Day;
	}

	static string getSystemTime() {
		time_t now = time(0);
		tm* localTime = localtime(&now);

		return to_string(localTime->tm_hour) + ":" + to_string(localTime->tm_min) + ":" + to_string(localTime->tm_sec);
	}

	static string getSystemDateTimeString() {
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));
	}
};