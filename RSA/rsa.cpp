#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <Windows.h>
#include <sstream>
using namespace std;

//алфавит
const char ALPHABET[34]{ ' ', 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я' };

//функция проверки на простое число
bool prime(int n) {
	bool k = true;
	if (n != 2) {
		for (int i = 2; i < (int)sqrt(n) + 1; i++) { //делим число на все числа до него 
			if (n % i == 0) { // если остаток 0, число не простое
				k = false;
				break;
			}
		}
	}
	return k;
}

//функция генерации простого числа
int genPrime() {
	int t = 10 + rand() % 90;
	do {
		t++;
	} while (!prime(t));

	return t;
}

//функция нахождения НОД методом Евклида
int evklid(int num1, int num2) {
	vector<int> r;
	int i = 1;
	r.push_back(max(num1, num2));
	r.push_back(min(num1, num2));
	while (r[i] != 0) {
		i++;
		r.push_back(r[i - 2] % r[i - 1]);
	}
	return r[i - 1];
}

//функция генерации взаимно простого числа
int genCoprime(int x) {
	int i = 1 + rand() % 99;
	do {
		i++;
	} while (evklid(x, i) != 1);
	return i;
}

//функция вычисления секретной экспоненты
int gend(int f, int e) {
	int i;
	for (i = 1; i < 100; i++) {
		if (((f * (i)+1) % e) == 0) {
			return (int)((f * (i)+1) / e);
		}
	}
	return 0;
}

//функция возведения в степень для больших чисел
long long int mul(int& x, int& k, int& n) {
	long long int res = 1;
	for (int i = 0; i < k; i++) {
		res = res * x % n;
	}
	return res;
}

//функция шифрования
void encrypt(string& out, const string& input,  int& e, int& n) {
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < sizeof(ALPHABET); j++) {
			if (ALPHABET[j] == input[i]) {
				int res = mul(j, e, n); //формула шифрования
				out += to_string(res);
				out += " ";
			}
		}
	}
}

//функция расшифровки
void decrypt(string& out1, const string& input, int& d, int& n) {
	stringstream text(input);
	string letter;
	while (text >> letter) {
		int code = stoi(letter);
		int r = mul(code, d, n); //фурмула расшифровки
		out1 += ALPHABET[r];
	}
}

int main() {
	using namespace std;

	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int e, d, n, f, p, q;

	string text = "";
	string out = "";
	string out1 = "";

	while (true) {
		p = genPrime();
		q = genPrime();

		n = p * q;
		f = (p - 1) * (q - 1);
	
		e = genCoprime(f);
		d = gend(f, e);
		cout << "Введите текст: ";
		getline(cin, text);
		encrypt(out,text,e,n);
		decrypt(out1, out, d, n);
		cout << "p = " << p << endl;
		cout << "q = " << q << endl;

		cout << "n = " << n << endl;
		cout << "f = " << f << endl;

		cout << "e = " << e << endl;
		cout << "d = " << d << endl;
		cout << "Зашифрованное сообщение: " << out << endl;
		cout << "Расшифрованное сообщение: " << out1 << endl;
		cout << "------------------------------------------------------------------------" << endl;
		text = "";
		out = "";
		out1 = "";
	}
}