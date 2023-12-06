#include <iostream>
#include <Windows.h>
#include <string>
#include <bitset>
#include <vector>
#include "getrand.h"

using namespace std;

//таблицы перестановок и замен
const vector<int> FIRST_PERM_TABLE = { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
									  62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
									  57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
									  61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };
const vector<int> FINAL_PERM_TABLE = { 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
									  38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
									  36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
									  34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25 };
const vector<int> EXTENSION_TABLE = { 32, 1, 2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
									 8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
									 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
									 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };
const vector<int> C_TABLE = { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
							 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36 };
const vector<int> D_TABLE = { 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
							 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 };
const vector<int> KI_TABLE = { 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 22, 4,
							  26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
							  51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };
const vector<int> P_PERM_TABLE = { 16, 7, 20, 21, 29, 12, 28, 17,
								  1, 15, 23, 26, 5, 18, 31, 10,
								  2, 8, 24, 14, 32, 27, 3, 9,
								  19, 13, 30, 6, 22, 11, 4, 25 };

const int S1[4][16] = {
		{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
		{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
		{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
		{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
};
const int S2[4][16] = {
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
		{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
		{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
		{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
};
const int S3[4][16] = {
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
		{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
		{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
		{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
};
const int S4[4][16] = {
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
		{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
		{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
		{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
};
const int S5[4][16] = {
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
		{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
		{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
		{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
};
const int S6[4][16] = {
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
		{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
		{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
		{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
};
const int S7[4][16] = {
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
		{ 13,0,11,7,4,9,1,10,14,3,5,10,2,15,8,6 },
		{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
		{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
};
const int S8[4][16] = {
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
		{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
		{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
		{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
};


bitset<64> stringToBits(const string str) {//Перевод строки из 8 символов в последовательность бит
	bitset<64> bits64;
	for (int i = 0; i < 8; i++) {
		bitset<8> bits8(str[i]);
		for (int j = 0; j < 8; j++) {
			bits64[static_cast<size_t>(i) * 8 + j] = bits8[j];
		}
	}
	return bits64;
}
string bitsToString(const bitset<64>& bits64) {//перевод из 64 бит в строку
	string text;
	bitset<8> bits8;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bits8[j] = bits64[static_cast<size_t>(i) * 8 + j];
		}
		text += char(bits8.to_ulong());
	}
	return text;
}

bitset<64> firstPermutation(const bitset<64>& bits64) {//начальная перестановка
	bitset<64> bits;
	for (int i = 0; i < 64; i++) {
		bits[i] = bits64[FIRST_PERM_TABLE[i] - 1];
	}
	return bits;
}
bitset<64> finalPermutation(const bitset<64>& bits64) {//конечная перестановка
	bitset<64> bits;
	for (int i = 0; i < 64; i++) {
		bits[i] = bits64[FINAL_PERM_TABLE[i] - 1];
	}
	return bits;
}
void pPermutation(bitset<32>& P) {//Перестановка в функции f
	bitset<32> temp = P;
	for (int i = 0; i < 32; i++) {
		P[i] = temp[P_PERM_TABLE[i] - 1];
	}
}
bitset<64> revfinalPermutation(const bitset<64>& bits64) {//Обратная начальная перестановка 
	bitset<64> bits;									  //для расшифровывания
	for (int i = 0; i < 64; i++) {
		bits[FINAL_PERM_TABLE[i] - 1] = bits64[i];
	}
	return bits;
}
bitset<64> revfirstPermutation(const bitset<64>& bits64) {//Обратная конечная перестановка
	bitset<64> bits;									  //для расшифровывания
	for (int i = 0; i < 64; i++) {
		bits[FIRST_PERM_TABLE[i] - 1] = bits64[i];
	}
	return bits;
}

void divByLR(const bitset<64> bits64, bitset<32>& L, bitset<32>& R) {//Разделение блока бит на 2 части
	for (int i = 0; i < 64; i++) {
		if (i < 32) {
			L[i] = bits64[i];
		}
		else { R[static_cast<size_t>(i) - 32] = bits64[i]; }
	}
}
void divByCD(const bitset<64> key, bitset<28>& C, bitset<28>& D) {//Разделение ключа на 2 части
	for (int i = 0; i < 28; i++) {								  //с исключанием битов четности по таблице
		C[i] = key[C_TABLE[i] - 1];
	}
	for (int i = 0; i < 28; i++) {
		D[i] = key[D_TABLE[i] - 1];
	}
}
bitset<64> LR(const bitset<32>& L, const bitset<32>& R) {//объединение двух блоков бит в один
	bitset<64> res;
	for (int i = 0; i < 64; i++) {
		if (i < 32) {
			res[i] = L[i];
		}
		else {
			res[i] = R[static_cast<size_t>(i) - 32];
		}
	}
	return res;
}

bitset<48> extensionFunc(const bitset<32>& R) {//функция расширения правой части блока до 48 бит
	bitset<48> extended;
	for (int i = 0; i < 48; i++) {
		extended[i] = R[EXTENSION_TABLE[i] - 1];
	}
	return extended;
}
bitset<4> S(const int& iter, const bitset<6>& S) {//функция S преобразования из 6 бит в 4 по таблицам Si
	bitset<2> row; bitset<4> col;
	row[1] = S[0]; row[0] = S[5];

	for (int i = 1; i < 5; i++) {
		col[4 - static_cast<size_t>(i)] = S[i];
	}
	int row_num = row.to_ulong(); int col_num = col.to_ulong();
	int num = 0;

	switch (iter)
	{
	case 0:
		num = S1[row_num][col_num];
		break;
	case 1:
		num = S2[row_num][col_num];
		break;
	case 2:
		num = S3[row_num][col_num];
		break;
	case 3:
		num = S4[row_num][col_num];
		break;
	case 4:
		num = S5[row_num][col_num];
		break;
	case 5:
		num = S6[row_num][col_num];
		break;
	case 6:
		num = S7[row_num][col_num];
		break;
	case 7:
		num = S8[row_num][col_num];
		break;
	}
	return bitset<4>(num);
}
bitset<32> transformS(const bitset<48>& extended) {//Разделение блока 48 бит на блоки по 6 бит
	bitset<32> res;								   //и сжатие до 4 бит функцией S
	bitset<6> bits6;
	bitset<4> bits4;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			bits6[j] = extended[static_cast<size_t>(i) * 6 + j];
		}
		bits4 = S(i, bits6);
		for (int k = 0; k < 4; k++) {
			res[k + 4 * static_cast<size_t>(i)] = bits4[k];
		}
	}
	return res;
}
bitset<48> genKeyI(const int& iter, bitset<28>& C, bitset<28>& D) {//Генерация ключа для кажой итерации
	if (iter == 0 || iter == 1 || iter == 8 || iter == 15) {
		C <<= 1;
		D <<= 1;
	}
	else {
		C <<= 2;
		D <<= 2;
	}

	bitset<56> key;
	for (int i = 0; i < 56; i++) {
		if (i < 28) {
			key[i] = C[i];
		}
		else {
			key[i] = D[static_cast<size_t>(i) - 28];
		}
	}

	bitset<48> keyI;
	for (int i = 0; i < 48; i++) {
		keyI[i] = key[KI_TABLE[i] - 1];
	}
	return keyI;
}
bitset<32> F(const bitset<32>& R, const bitset<48>& K) {//Основная функция шифрования (функция Фейстеля)
	bitset<32> f;
	bitset<48> extended = extensionFunc(R);
	extended = extended ^ K;
	f = transformS(extended);
	pPermutation(f);
	return f;
}

bitset<64> encryptDES(const bitset<64>& bits, const bitset<64>& key) {//Функция шифрования
	bitset<64> res;
	bitset<64> perm = firstPermutation(bits);//начальная перестановка
	bitset<32> L; bitset<32> R;
	divByLR(perm, L, R);//разделение блока на 2 половины
	bitset<28> C; bitset<28> D;
	divByCD(key, C, D);//разделение ключа на 2 половины с исключением битов четности

	for (int i = 0; i < 16; i++) {//16 раундов шифрования
		bitset<32> Li = R;
		bitset<48> keyI = genKeyI(i, C, D);//генериция i-го ключа
		bitset<32> f = F(R, keyI);//Основная функция шифрования
		L ^= f;
		if (i != 15) {
			R = L;
			L = Li;
		}
	}
	res = finalPermutation(LR(L, R));//конечная перестановка
	//cout << res;
	return res;
}


//функция шифрования/расшифровки блока в режиме связи по шифротексту
bitset<64> DES_CFB(const bitset<64>& bits, const bitset<64>& key, bitset<64>& vec_init, const int& L, const string& mode) {
	bitset<64> reg1; //регистр1
	bitset<64> reg2; //регистр2
	bitset<64> cipher; //заширфрованный регистр1
	bitset<64> block; //блок из изсходного текста L бит
	bitset<64> shr; //блок из регистра 2 L бит
	bitset<64> AND; //сумма по модулю2
	bitset<64> res; //зашифрованное/расшифрованное сообщение
	reg1 = vec_init;
	for (int i = 0; i < (64 / L); i++) { // для целых блоков по 64 бита
		cipher = encryptDES(reg1, key); //шифруем регистр1
		reg2 = cipher;

		for (int j = 0; j < L; j++) {//выбираем L бит из регистра2
			shr[j] = reg2[j];
		}

		for (int j = 0; j < L; j++) { //выбираем L бит из входного сообщения
			block[j] = bits[i * L + j];
		}
		 
		AND = shr ^ block; //складываем по модулю 2

		for (int j = 0; j < L; j++) { //добавляем значение суммы к выходному сообщению
			res[i * L + j] = AND[j];
		}

		reg1 <<= L; // сдвигаем регистр 1 на L бит
		for (int j = 0; j < L; j++) {
			if (mode == "encrypt") { //при шифровке
				reg1[j] = AND[j]; // заносим в конец регистра1 сумму по модулю2
			}
			else if (mode == "decrypt") {// при расшифровке 
				reg1[j] = block[j]; // заносим в регистр 1 блок L бит из входного текста
			}
		}
	}
	//обнуляем блоки
	block.reset();
	shr.reset();
	AND.reset();

	if ((64 % L) != 0) {//для не целого блока бит
		cipher = encryptDES(reg1, key);
		reg2 = cipher;

		for (int j = 0; j < (64%L); j++) {
			shr[j] = reg2[j];
		}

		for (int j = 0; j < (64%L); j++) {
			block[j] = bits[(64/L) * L + j];
		}

		AND = shr ^ block;

		for (int j = 0; j < (64%L); j++) {
			res[(64/L) * L + j] = AND[j];
		}

		reg1 <<= L;
		for (int j = 0; j < (64%L); j++) {
			if (mode == "encrypt") {
				reg1[j] = AND[j];
			}
			else if (mode == "decrypt") {
				reg1[j] = block[j];
			}
		}
	}
	vec_init = reg1;
	return res;
}

//функция шифра
string crypt(const string& text, const string& key, const string& vec, const int& L, const string& mode) {
	string res = "";
	bitset<64> k = stringToBits(key);//переводим в биты ключ
	bitset<64> v = stringToBits(vec);//переводим в биты вектор инициализации

	//если размер текста кратен 8
	if ((text.size() % 8) == 0) {
		for (unsigned int i = 0; i < text.size() / 8; i++) {
			string mid = "";
			for (int j = 0; j < 8; j++) {
				mid += text[i * 8 + j];
			}
			bitset<64> bits = stringToBits(mid);
			bitset<64> r = DES_CFB(bits,k,v,L,mode);
			string block = bitsToString(r);
			res += block;
		}
	}
	//елси не кратен
	else {
		for (unsigned int i = 0; i < (text.size() / 8) + 1; i++) {
			if (i != (text.size() / 8)) {//цельные блоки по 8 символов
				string mid = "";
				for (int j = 0; j < 8; j++) {
					mid += text[i * 8 + j];
				}
				bitset<64> bits = stringToBits(mid);
				bitset<64> r = DES_CFB(bits, k, v, L, mode);
				string block = bitsToString(r);
				res += block;
			}
			else {//обработка последнего блока в котромо меньше 8 символов
				string mid = "";
				for (int j = 0; j < (text.size() % 8); j++) {
					mid += text[i * 8 + j];
				}
				for (int j = 0; j < (8 - (text.size() % 8)); j++) {
					mid += " ";
				}
				bitset<64> bits = stringToBits(mid);
				bitset<64> r = DES_CFB(bits, k, v, L, mode);
				string block = bitsToString(r);
				res += block;
			}
		}
	}
	return res;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string text = "";
	string key = "";
	string vec = "";
	string out = "";
	int L = GetRandomNumber(1, 64);


	while (true) {
		cout << "Введите текст: ";
		getline(cin, text);
		cout << "Введите ключ(8 символов): ";
		getline(cin, key);
		while (key.size() != 8) {
			cout << "Некорректный размер ключа! Попробуйте снова: ";
			getline(cin, key);
		}
		cout << "Введите вектор инициализации(8 символов): ";
		getline(cin, vec);
		while (vec.size() != 8) {
			cout << "Некорректный размер вектора! Попробуйте снова: ";
			getline(cin, vec);
		}
		out = crypt(text, key, vec, L, "encrypt");
		cout << "Зашифрованное сообщение: " << out << endl;

		cout << "Расшифрованное сообщение: " << crypt(out, key, vec, L, "decrypt") << endl;
		cout << "--------------------------------------------------------------------------" << endl;
	}
}