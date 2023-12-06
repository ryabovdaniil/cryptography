#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <windows.h>
#include "getrand.h"
#include <sstream>
#include <algorithm>

using namespace std;

//�������
const map<string, vector<int>> alphabet = {
										   {"�",{21,40,10,78,86}},	{"�",{37,26}},			{"�",{14,63,71,87}},
										   {"�",{22,47}},			{"�",{1,31,15,79}},		{"�",{24,83,70,49,76}},
										   {"�",{62}},				{"�",{73,30}},			{"�",{46,2,90,50,81}},
										   {"�",{88,11}},			{"�",{23,91,69,55}},	{"�",{12,72,38,3}},
										   {"�",{8,32,61,82}},		{"�",{27,77,54,85,51}},	{"�",{53,68,9,34,92}},
										   {"�",{35,60,84}},		{"�",{4,44,45,33,18}},	{"�",{20,52,89,80,66}},
										   {"�",{13,39,67,64,5}},	{"�",{59,07,93}},		{"�",{25}},
										   {"�",{75}},				{"�",{43}},				{"�",{19,58}},
										   {"�",{29}},				{"�",{6}},				{"�",{65}},
										   {"�",{74,17,42}},		{"�",{48,56}},			{"�",{36}},
										   {"�",{28}},				{"�",{16,41,57}},		{" ", {99,179,100,122,111}}
};

//������� ����������
string encrypt(const string& open_text) {
	string close_text; //������������� ���������
	for (const char& ch : open_text) { //������� �������� ��������� ���������
		for (const auto& alph : alphabet) {
			string letter(1, ch);
			if (letter == alph.first) { // ��������� ������� � �������� � ��������
				close_text += to_string(alph.second[GetRandomNumber(0, alph.second.size() - 1)]) + " ";//��������� ����� ��������, ����������������
				break;																			  //������� � ��������
			}
		}
	}
	return close_text;
}

//������� ���������������
string decrypt(const string& close_text) {
	string open_text; //�������������� ���������
	stringstream text(close_text);
	string letter;
	while (text >> letter) { // ������ ������������� ������ �� ��������� ��������� ��������
		int code = stoi(letter); //���������� �������� � �������������� ����
		for (const auto& alph : alphabet) {
			for (const int& alphabet_code : alph.second) {
				if (code == alphabet_code) {//����� � �������� ��������, ������� ��������� � ������������� ���������
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
		cout << "������� ��������(�����������/������������): ";
		string answer;
		getline(cin, answer);

		string text;

		if (answer == "�����������") {
			cout << "������� �����:" << endl;
			getline(cin, text);
			transform(text.begin(), text.end(), text.begin(), tolower);
			cout << encrypt(text) << endl;
		}
		else if (answer == "������������") {
			cout << "������� ����:" << endl;
			getline(cin, text);
			cout << decrypt(text) << endl;
		}
		else {
			cout << "������������ ��������!" << endl;
		}
	}

}
