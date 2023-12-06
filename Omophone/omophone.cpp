#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <windows.h>
#include "getrand.h"
#include <sstream>
#include <algorithm>

using namespace std;

//алфавит
const map<string, vector<int>> alphabet = {
										   {"а",{21,40,10,78,86}},	{"б",{37,26}},			{"в",{14,63,71,87}},
										   {"г",{22,47}},			{"д",{1,31,15,79}},		{"е",{24,83,70,49,76}},
										   {"ж",{62}},				{"з",{73,30}},			{"и",{46,2,90,50,81}},
										   {"й",{88,11}},			{"к",{23,91,69,55}},	{"л",{12,72,38,3}},
										   {"м",{8,32,61,82}},		{"н",{27,77,54,85,51}},	{"о",{53,68,9,34,92}},
										   {"п",{35,60,84}},		{"р",{4,44,45,33,18}},	{"с",{20,52,89,80,66}},
										   {"т",{13,39,67,64,5}},	{"у",{59,07,93}},		{"ф",{25}},
										   {"х",{75}},				{"ц",{43}},				{"ч",{19,58}},
										   {"ш",{29}},				{"щ",{6}},				{"ъ",{65}},
										   {"ы",{74,17,42}},		{"ь",{48,56}},			{"э",{36}},
										   {"ю",{28}},				{"я",{16,41,57}},		{" ", {99,179,100,122,111}}
};

//функция шифрования
string encrypt(const string& open_text) {
	string close_text; //зашифрованное сообщение
	for (const char& ch : open_text) { //перебор символов открытого сообщения
		for (const auto& alph : alphabet) {
			string letter(1, ch);
			if (letter == alph.first) { // сравнение символа с символом в алфавите
				close_text += to_string(alph.second[GetRandomNumber(0, alph.second.size() - 1)]) + " ";//случайный выбор значения, соответствующего
				break;																			  //символу в алфавите
			}
		}
	}
	return close_text;
}

//функция расшифровывания
string decrypt(const string& close_text) {
	string open_text; //расшифрованное сообщение
	stringstream text(close_text);
	string letter;
	while (text >> letter) { // разбор зашифрованной строки на отдельные заначения символов
		int code = stoi(letter); //приведение значения к целочисленному типу
		for (const auto& alph : alphabet) {
			for (const int& alphabet_code : alph.second) {
				if (code == alphabet_code) {//поиск в алфавите значения, которое находится в зашифрованном сообщении
					open_text += alph.first;
					break;
				}
			}
		}
	}
	return open_text;
}



int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		cout << "Введите действие(зашифровать/расшифровать): ";
		string answer;
		getline(cin, answer);

		string text;

		if (answer == "зашифровать") {
			cout << "Введите текст:" << endl;
			getline(cin, text);
			transform(text.begin(), text.end(), text.begin(), tolower);
			cout << encrypt(text) << endl;
		}
		else if (answer == "расшифровать") {
			cout << "Введите шифр:" << endl;
			getline(cin, text);
			cout << decrypt(text) << endl;
		}
		else {
			cout << "Недопустимое действие!" << endl;
		}
	}

}
