#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

//алфавит
const map<char, int> alphabet1 = { {'а',0},{'б',1},{'в',2},{'г',3},{'д',4},{'е',5},{'ж',6},{'з',7},{'и',8},{'й',9},{'к',10},{'л',11},{'м',12},{'н',13},{'о',14},{'п',15},{'р',16},{'с',17},{'т',18},{'у',19 },{'ф',20},{'х',21},{'ц',22},{'ч',23},{'ш',24},{'щ',25},{'ъ',26},{'ы',27},{'ь',28},{'э',29},{'ю',30},{'я',31},{' ',32} };

//функция шифрования/расшифровывания
string encrypt(const string& open_text, const string& gamma) {
	string close_text = ""; //зашифрованное/расшифрованное сообщение
	int res;
	for (int i = 0; i < open_text.size(); i++) { //получение индексов символов текста и гаммы
		res = int(alphabet1.at(open_text[i]) ^ alphabet1.at(gamma[i]));//сложение по модулю 2 индексов символов сообщения и гаммы из алфавита
		if (res > alphabet1.size()) { //если выход за диапазон индексов алфавита
			res = alphabet1.size() - 1; //то ставится пробел
		}
		for (const auto& alph : alphabet1) { //выбор символа в алфавите по индексу, равному суммо по модулю 2
			if (alph.second == res) {
				close_text += alph.first;
				break;
			}
		}
	}
	return close_text;
}

//определение гаммы шифра(повторени ключа до конца сообщения)
void define_gamma(const string& text, const string& key, string& gamma) {
	if (text.size() == key.size()) {//если размер сообщения равен разимеру ключа
		gamma = key;//то гамма равна ключу
	}
	else {
		while (gamma.size() < text.size()) { //пока размер гаммы меньше размера сообщения
			for (const char& ch1 : key) { //циклическое получение символа из ключа
				if (gamma.size() == text.size()) {//если размер гаммы равен размеру сообщения
					break;// тогда выход
				}
				else gamma += ch1;//иначе к гамме добавляем текущий символ
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
		cout << "Введите действие(зашифровать/расшифровать): ";
		string answer;
		getline(cin, answer);
		string text, gamma, key = "";

		if (answer == "зашифровать") {
			cout << "Введите текст: ";
			getline(cin, text);
			do
			{
				cout << "Введите ключ меньший или равный длинне текста: ";
				getline(cin, key);
			} while (key.size() > text.size());
			transform(text.begin(), text.end(), text.begin(), tolower);
			transform(key.begin(), key.end(), key.begin(), tolower);
			define_gamma(text, key, gamma);
			cout << encrypt(text, gamma) << endl;
		}
		else if (answer == "расшифровать") {
			cout << "Введите шифр: ";
			getline(cin, text);
			do
			{
				cout << "Введите ключ меньший или равный длинне текста: ";
				getline(cin, key);
			} while (key.size() > text.size());
			transform(text.begin(), text.end(), text.begin(), tolower);
			transform(key.begin(), key.end(), key.begin(), tolower);
			define_gamma(text, key, gamma);
			cout << encrypt(text, gamma) << endl;
		}
		else {
			cout << "Недопустимое действие!" << endl;
		}
	}
}
