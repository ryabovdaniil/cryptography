#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

//�������
const map<char, int> alphabet1 = { {'�',0},{'�',1},{'�',2},{'�',3},{'�',4},{'�',5},{'�',6},{'�',7},{'�',8},{'�',9},{'�',10},{'�',11},{'�',12},{'�',13},{'�',14},{'�',15},{'�',16},{'�',17},{'�',18},{'�',19 },{'�',20},{'�',21},{'�',22},{'�',23},{'�',24},{'�',25},{'�',26},{'�',27},{'�',28},{'�',29},{'�',30},{'�',31},{' ',32} };

//������� ����������/���������������
string encrypt(const string& open_text, const string& gamma) {
	string close_text = ""; //�������������/�������������� ���������
	int res;
	for (int i = 0; i < open_text.size(); i++) { //��������� �������� �������� ������ � �����
		res = int(alphabet1.at(open_text[i]) ^ alphabet1.at(gamma[i]));//�������� �� ������ 2 �������� �������� ��������� � ����� �� ��������
		if (res > alphabet1.size()) { //���� ����� �� �������� �������� ��������
			res = alphabet1.size() - 1; //�� �������� ������
		}
		for (const auto& alph : alphabet1) { //����� ������� � �������� �� �������, ������� ����� �� ������ 2
			if (alph.second == res) {
				close_text += alph.first;
				break;
			}
		}
	}
	return close_text;
}

//����������� ����� �����(��������� ����� �� ����� ���������)
void define_gamma(const string& text, const string& key, string& gamma) {
	if (text.size() == key.size()) {//���� ������ ��������� ����� �������� �����
		gamma = key;//�� ����� ����� �����
	}
	else {
		while (gamma.size() < text.size()) { //���� ������ ����� ������ ������� ���������
			for (const char& ch1 : key) { //����������� ��������� ������� �� �����
				if (gamma.size() == text.size()) {//���� ������ ����� ����� ������� ���������
					break;// ����� �����
				}
				else gamma += ch1;//����� � ����� ��������� ������� ������
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		cout << "������� ��������(�����������/������������): ";
		string answer;
		getline(cin, answer);
		string text, gamma, key = "";

		if (answer == "�����������") {
			cout << "������� �����: ";
			getline(cin, text);
			do
			{
				cout << "������� ���� ������� ��� ������ ������ ������: ";
				getline(cin, key);
			} while (key.size() > text.size());
			transform(text.begin(), text.end(), text.begin(), tolower);
			transform(key.begin(), key.end(), key.begin(), tolower);
			define_gamma(text, key, gamma);
			cout << encrypt(text, gamma) << endl;
		}
		else if (answer == "������������") {
			cout << "������� ����: ";
			getline(cin, text);
			do
			{
				cout << "������� ���� ������� ��� ������ ������ ������: ";
				getline(cin, key);
			} while (key.size() > text.size());
			transform(text.begin(), text.end(), text.begin(), tolower);
			transform(key.begin(), key.end(), key.begin(), tolower);
			define_gamma(text, key, gamma);
			cout << encrypt(text, gamma) << endl;
		}
		else {
			cout << "������������ ��������!" << endl;
		}
	}
}
