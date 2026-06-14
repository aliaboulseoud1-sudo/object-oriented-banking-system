//// *************** MY SOLUTION ***************
//
//
//#pragma once
//
//#include <iostream>
//#include <vector>
//using namespace std;
//
//class clsString
//{
//private:
//    string _Value;
//
//    static bool _IsVowel(char ch) {
//        ch = tolower(ch);
//
//        return ((ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u'));
//    }
//
//    static char _InvertCharacterCase(char ch) {
//        return isupper(ch) ? tolower(ch) : toupper(ch);
//    }
//
//public:
//    clsString() {
//        _Value = "";
//    }
//
//    clsString(string Value) {
//        _Value = Value;
//    }
//
//    void setValue(string Value) {
//        _Value = Value;
//    }
//
//    string getValue() {
//        return _Value;
//    }
//
//    static short CountWords(string S1) {
//        string delim = " "; // delimiter
//        short Counter = 0;
//        short pos = 0;
//        string sWord; // define a string variable
//
//        // use find() function to get the position of the delimiters
//        while ((pos = S1.find(delim)) != std::string::npos) {
//            sWord = S1.substr(0, pos); // store the word
//            if (sWord != "") {
//                Counter++;
//            }
//
//            //erase() until position and move to next word.
//            S1.erase(0, pos + delim.length());
//        }
//
//        if (S1 != "") {
//            Counter++; // it counts the last word of the string.
//        }
//
//        return Counter;
//    }
//
//    short CountWords() {
//        return CountWords(_Value);
//    }
//
//    static vector <string> Split(string S1, string Delim) {
//        vector <string> vString;
//
//        short pos = 0;
//        string sWord;
//
//        while ((pos = S1.find(Delim)) != std::string::npos) {
//            sWord = S1.substr(0, pos);
//            if (sWord != "") {
//                vString.push_back(sWord);
//            }
//
//            S1.erase(0, pos + Delim.length());
//        }
//
//        if (S1 != "") {
//            vString.push_back(S1);
//        }
//
//        return vString;
//    }
//
//    vector <string> Split(string Delim) {
//        return Split(_Value, Delim);
//    }
//
//    static short CountVowels(string str) {
//        short Counter = 0;
//
//        for (short i = 0; i < str.length(); i++) {
//            if (_IsVowel(str[i])) {
//                Counter++;
//            }
//        }
//
//        return Counter;
//    }
//
//    short CountVowels() {
//        return CountVowels(_Value);
//    }
//
//    static string JoinString(vector <string> vstring, string delimiter) {
//        string str = "";
//
//        for (string& word : vstring) {
//            str = str + word + delimiter;
//        }
//
//        return str.substr(0, str.length() - delimiter.length());
//    }
//
//    static void PrintFirstLetterOfEachWord(string str) {
//        bool isNewWord = true;
//
//        for (int i = 0; i < str.length(); i++) {
//            if (str[i] != ' ' && isNewWord) {
//                cout << str[i] << endl;
//                isNewWord = false;
//            }
//            else if (str[i] == ' ') {
//                isNewWord = true;
//            }
//        }
//    }
//
//    void PrintFirstLetterOfEachWord() {
//        PrintFirstLetterOfEachWord(_Value);
//    }
//
//    static string UpperFirstLetterOfEachWord(string str) {
//        bool isFirstLetter = true;
//
//        for (int i = 0; i < str.length(); i++) {
//            if (str[i] != ' ' && isFirstLetter) {
//                str[i] = (char)toupper(str[i]);
//            }
//            isFirstLetter = (str[i] == ' ' ? true : false);
//        }
//        return str;
//    }
//
//    string UpperFirstLetterOfEachWord() {
//        return UpperFirstLetterOfEachWord(_Value);
//    }
//
//    static string LowerFirstLetterOfEachWord(string str) {
//        bool isFirstLetter = true;
//
//        for (int i = 0; i < str.length(); i++) {
//            if (str[i] != ' ' && isFirstLetter) {
//                str[i] = (char)tolower(str[i]);
//            }
//            isFirstLetter = (str[i] == ' ' ? true : false);
//        }
//        return str;
//    }
//
//    string LowerFirstLetterOfEachWord() {
//        return LowerFirstLetterOfEachWord(_Value);
//    }
//
//    static string UpperString(string str) {
//        for (int i = 0; i < str.length(); i++) {
//            str[i] = (char)toupper(str[i]);
//        }
//        return str;
//    }
//
//    string UpperString() {
//        return UpperString(_Value);
//    }
//
//    static string LowerString(string str) {
//        for (int i = 0; i < str.length(); i++) {
//            str[i] = (char)tolower(str[i]);
//        }
//        return str;
//    }
//
//    string LowerString() {
//        return LowerString(_Value);
//    }
//
//    static string InvertAllLetterCase(string str) {
//        for (int i = 0; i < str.length(); i++) {
//            str[i] = _InvertCharacterCase(str[i]);
//        }
//        return str;
//    }
//
//    string InvertAllLetterCase() {
//        return InvertAllLetterCase(_Value);
//    }
//
//    static int CountCapitalLetters(string str) {
//        int Counter = 0;
//        for (int i = 0; i < str.length(); i++) {
//            if (isupper(str[i])) {
//                Counter++;
//            }
//        }
//        return Counter;
//    }
//
//    int CountCapitalLetters() {
//        return CountCapitalLetters(_Value);
//    }
//
//    static int CountSmallLetters(string str) {
//        int Counter = 0;
//        for (int i = 0; i < str.length(); i++) {
//            if (islower(str[i])) {
//                Counter++;
//            }
//        }
//        return Counter;
//    }
//
//    int CountSmallLetters() {
//        return CountSmallLetters(_Value);
//    }
//
//    static short CountLetter(string str, char ch, bool MatchCase = true) {
//        short Counter = 0;
//        for (int i = 0; i < str.length(); i++) {
//            if (MatchCase) {
//                if (str[i] == ch) {
//                    Counter++;
//                }
//            }
//            else {
//                if (tolower(str[i]) == tolower(ch)) {
//                    Counter++;
//                }
//            }
//
//        }
//        return Counter;
//    }
//
//    short CountLetter(char ch, bool MatchCase = true) {
//        return CountLetter(_Value, ch, MatchCase);
//    }
//
//    static void PrintAllVowelsInString(string str) {
//        cout << "\nVowels in the string are: ";
//        for (short i = 0; i < str.length(); i++) {
//            if (_IsVowel(str[i])) {
//                cout << str[i] << "   ";
//            }
//        }
//        cout << endl;
//    }
//
//    void PrintAllVowelsInString() {
//        PrintAllVowelsInString(_Value);
//    }
//
//    static void PrintEachWordInString(string str) {
//        string delimiter = " ";
//
//        cout << "\nYour string words are: \n\n";
//
//        short pos = 0;
//        string sWord;
//        while ((pos = str.find(delimiter)) != std::string::npos) {
//            sWord = str.substr(0, pos);
//            if (sWord != "") {
//                cout << sWord << endl;
//            }
//            str.erase(0, pos + delimiter.length());
//        }
//
//        if (str != "") {
//            cout << str << endl;
//        }
//    }
//
//    void PrintEachWordInString() {
//        PrintEachWordInString(_Value);
//    }
//
//    static string TrimLeft(string str) {
//        for (short i = 0; i < str.length(); i++) {
//            if (str[i] != ' ') {
//                str.erase(0, i);
//                break;
//            }
//        }
//
//        return str;
//    }
//
//    string TrimLeft() {
//        return TrimLeft(_Value);
//    }
//
//    static string TrimRight(string str) {
//        for (short i = str.length() - 1; i >= 0; i--) {
//            if (str[i] != ' ') {
//                str.erase(i + 1); // i + 1 --> Start
//                break;
//            }
//        }
//
//        return str;
//    }
//
//    string TrimRight() {
//        return TrimRight(_Value);
//    }
//
//    static string Trim(string str) {
//        return  TrimLeft(TrimRight(str));
//    }
//
//    string Trim() {
//        return Trim(_Value);
//    }
//
//    static string ReverseStringWords(vector <string> vstring, string delimiter = " ") {
//        string str = "";
//        vector<string>::iterator iter = vstring.end();
//
//        while (iter != vstring.begin()) {
//            --iter;
//            str += *iter + delimiter;
//        }
//
//        return str.substr(0, str.length() - delimiter.length());
//    }
//
//    static string ReplaceWord(string str, string WordToReplace, string  WordReplaceTo) {
//        short Pos = str.find(WordToReplace);
//
//        while (Pos != std::string::npos) {
//            str = str.replace(Pos, WordToReplace.length(), WordReplaceTo);
//            Pos = str.find(WordToReplace);
//        }
//
//        return str;
//    }
//
//    string ReplaceWord(string WordToReplace, string  WordReplaceTo) {
//        return ReplaceWord(_Value, WordToReplace, WordReplaceTo);
//    }
//
//    static string RemoveAllPunctuations(string str) {
//        for (int i = 0; i < str.length(); i++) {
//            if (ispunct(str[i])) {
//                str.erase(i, 1);
//                i--;
//            }
//        }
//
//        return str;
//    }
//
//    string RemoveAllPunctuations() {
//        return RemoveAllPunctuations(_Value);
//    }
//
//    static short Length(string str) {
//        return str.length();
//    }
//
//    short Length() {
//        return _Value.length();
//    }
//};




#pragma once

#include <iostream>
#include <vector>
using namespace std;

class clsString {
private:
    string _Value;

public:
    clsString() {
        _Value = "";
    }

    clsString(string Value) {
        _Value = Value;
    }

    void setValue(string Value) {
        _Value = Value;
    }

    string getValue() {
        return _Value;
    }

    static short Length(string S1) {
        return S1.length();
    }

    short Length() {
        return _Value.length();
    }

    static short CountWords(string S1) {
        string delim = " "; // delimiter  
        short Counter = 0;
        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(delim)) != std::string::npos) {
            sWord = S1.substr(0, pos); // store the word   
            if (sWord != "") {
                Counter++;
            }

            //erase() until position and move to next word.
            S1.erase(0, pos + delim.length());
        }

        if (S1 != "") {
            Counter++; // it counts the last word of the string.
        }

        return Counter;
    }

    short CountWords() {
        return CountWords(_Value);
    }

    static string  UpperFirstLetterOfEachWord(string S1) {
        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);

        }

        return S1;
    }

    void  UpperFirstLetterOfEachWord() {
        // no need to return value , this function will directly update the object value  
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string  LowerFirstLetterOfEachWord(string S1) {
        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++) {
            if (S1[i] != ' ' && isFirstLetter) {
                S1[i] = tolower(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    void  LowerFirstLetterOfEachWord() {
        // no need to return value , this function will directly update the object value  
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string  UpperAllString(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

    void  UpperAllString() {
        _Value = UpperAllString(_Value);
    }

    static string  LowerAllString(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = tolower(S1[i]);
        }

        return S1;
    }

    void  LowerAllString() {
        _Value = LowerAllString(_Value);
    }

    static char  InvertLetterCase(char char1) {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static string  InvertAllLettersCase(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = InvertLetterCase(S1[i]);
        }

        return S1;
    }

    void  InvertAllLettersCase() {
        _Value = InvertAllLettersCase(_Value);
    }

    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

    static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All) {
        if (WhatToCount == enWhatToCount::All) {
            return S1.length();
        }

        short Counter = 0;

        for (short i = 0; i < S1.length(); i++) {
            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
                Counter++;

            if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
                Counter++;
        }

        return Counter;
    }

    static short  CountCapitalLetters(string S1) {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++) {
            if (isupper(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short  CountCapitalLetters() {
        return CountCapitalLetters(_Value);
    }

    static short  CountSmallLetters(string S1) {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++) {
            if (islower(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short  CountSmallLetters() {
        return CountSmallLetters(_Value);
    }

    static short  CountSpecificLetter(string S1, char Letter, bool MatchCase = true) {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++) {
            if (MatchCase) {
                if (S1[i] == Letter)
                    Counter++;
            }
            else {
                if (tolower(S1[i]) == tolower(Letter))
                    Counter++;
            }
        }

        return Counter;
    }

    short  CountSpecificLetter(char Letter, bool MatchCase = true) {
        return CountSpecificLetter(_Value, Letter, MatchCase);
    }

    static bool IsVowel(char Ch1) {
        Ch1 = tolower(Ch1);

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    static short  CountVowels(string S1) {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++) {
            if (IsVowel(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short  CountVowels() {
        return CountVowels(_Value);
    }

    static vector<string> Split(string S1, string Delim) {
        vector<string> vString;

        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(Delim)) != std::string::npos) {
            sWord = S1.substr(0, pos); // store the word   
            //if (sWord != "") {
            vString.push_back(sWord);
            //}

            S1.erase(0, pos + Delim.length());  /* erase() until position and move to next word. */
        }

        if (S1 != "") {
            vString.push_back(S1); // it adds last word of the string.
        }

        return vString;
    }

    vector<string> Split(string Delim) {
        return Split(_Value, Delim);
    }

    static string TrimLeft(string str) {
        for (short i = 0; i < str.length(); i++) {
            if (str[i] != ' ') {
                str.erase(0, i);
                break;
            }
        }

        return str;
    }

    void TrimLeft() {
        _Value = TrimLeft(_Value);
    }

    static string TrimRight(string str) {
        for (short i = str.length() - 1; i >= 0; i--) {
            if (str[i] != ' ') {
                str.erase(i + 1); // i + 1 --> Start
                break;
            }
        }

        return str;
    }

    void TrimRight() {
        _Value = TrimRight(_Value);
    }

    static string Trim(string str) {
        return (TrimLeft(TrimRight(str)));

    }

    void Trim() {
        _Value = Trim(_Value);
    }

    static string JoinString(vector<string> vString, string Delim) {
        string S1 = "";

        for (string& s : vString) {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static string JoinString(string arrString[], short Length, string Delim) {
        string S1 = "";

        for (short i = 0; i < Length; i++) {
            S1 = S1 + arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static string ReverseWordsInString(string S1) {
        vector<string> vString;
        string S2 = "";

        vString = Split(S1, " ");

        // declare iterator
        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin()) {

            --iter;

            S2 += *iter + " ";

        }

        S2 = S2.substr(0, S2.length() - 1); //remove last space.

        return S2;
    }

    void ReverseWordsInString() {
        _Value = ReverseWordsInString(_Value);
    }

    static string ReplaceWord(string S1, string StringToReplace, string ReplaceTo, bool MatchCase = true) {
        vector<string> vString = Split(S1, " ");

        for (string& s : vString) {
            if (MatchCase) {
                if (s == StringToReplace) {
                    s = ReplaceTo;
                }
            }
            else {
                if (LowerAllString(s) == LowerAllString(StringToReplace)) {
                    s = ReplaceTo;
                }
            }
        }

        return JoinString(vString, " ");
    }

    void ReplaceWord(string StringToReplace, string ReplaceTo) {
        _Value = ReplaceWord(_Value, StringToReplace, ReplaceTo);
    }

    static string RemovePunctuations(string S1) {
        string S2 = "";

        for (short i = 0; i < S1.length(); i++) {
            if (!ispunct(S1[i])) {
                S2 += S1[i];
            }
        }

        return S2;
    }

    void RemovePunctuations() {
        _Value = RemovePunctuations(_Value);
    }
};