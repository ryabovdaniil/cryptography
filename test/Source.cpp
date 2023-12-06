#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <vector>

using namespace std;

const char arr[45]{ ' ', 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','ы','ю','я','0','1','2','3','4','5','6','7','8','9' };

//проверка на то простое ли число
bool simple(int n) {
    for (int i = 2; i <= n / 2; i++) if ((n % i) == 0) return false;
    return true;
}

//перевод символов сообщения в числовые значения
void toNumber(string str, long long int* arr1) {
    for (int i = 0; i < str.length(); i++) {
        for (int j = 0; j < 44; j++) {
            if (str[i] == arr[j]) { arr1[i] = j; continue; }
        }
    }

}

//перевод чисел в символы
string toChar(long long int* arr1, string str, int n) {
    str.resize(n);
    for (int i = 0; i < n; i++) {
        str[i] = arr[arr1[i]];
    }
    return str;
}

//функция нахождения степени числа по модулю n
long long int Mod(int x, int step, int mod) {
    long long int res = 1;
    for (int i = 0; i < step; i++) {
        res = (res * x) % mod;
    }
    return res;
}

//структура ключа
struct Key {
    int a;
    int b;
    // перегрузка оператора присвоения
    Key operator = (Key key1) {
        a = key1.a;
        b = key1.b;
        return *this;
    }



};

//класс человека 
class Human {
    string str;       //сообщение
    string cryptMes;  //зашифрованное сообщение
    int p = 0;
    int q = 0;
    int n = 0;
    Key openKey;      //открытый ключ
    Key closeKey;     //закрытый ключ
public:
    string name;      //имя человека

    // метод для задания значений p и q
    void getPQ() {
        cout << "p и q должны быть простыми." << endl;
        cout << "Введите p: ";
        cin >> p;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << "Введите q: ";
        cin >> q;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
    }

    // метод создания открытого и закрытого ключа
    void createKey() {
        cout << name << " создает открытый и закрытый ключи." << endl;
        getPQ();
        n = p * q;
        int f = (p - 1) * (q - 1);
        int e = 0;
        for (int i = 2; i < f; i++)  if (simple(i) && f % i != 0) { e = i; break; }  //вычисление открытого ключа
        openKey.a = e;
        openKey.b = n;

        //вычисление закрытого ключа
        int d = 0;
        for (int i = 2; i < n; i++) {
            if ((i * e) % f == 1) { d = i; }
        }
        closeKey.a = d;
        closeKey.b = n;

        cout << "Открытый ключ: {" << openKey.a << "," << openKey.b << "}" << endl;
        cout << "Закрытый ключ: {" << closeKey.a << "," << closeKey.b << "}" << endl;

    }

    //метод получения открытого ключа от другого человека
    void getKey(Human f) {
        cout << name << " берет открытый ключ у " << f.name << endl;
        openKey = f.pushKey();
        n = openKey.b;
        cout << "{" << openKey.a << "," << openKey.b << "}" << endl;
    }

    //метод для того чтобы отдать открытый ключ
    Key pushKey() {
        return openKey;
    }

    // шифрование сообщения
    void encryptMessage() {

        cout << "Введите сообщение" << endl;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        getline(cin, str);
        cin.ignore(cin.rdbuf()->in_avail(), '\n');

        cout << name << " шифрует сообщение полученным открытым ключем." << endl;
        long long int* arr = new long long int[str.length()];
        toNumber(str, arr);

        for (int i = 0; i < str.length(); i++) {
            arr[i] = Mod(arr[i], openKey.a, n);
            cryptMes.append(to_string(arr[i]));
            cryptMes.append(" ");
        }
        this->showCrypt();

        delete[] arr;
    }

    //метод для того чтобы отдать зашифрованное сообщение другому человеку
    string sendMess() {
        return cryptMes;
    }

    //метод для получения от человека зашифрованного сообщения
    void getMes(Human f) {
        cout << name << " получает зашифрованное сообщение от " << f.name << endl;
        cryptMes = f.sendMess();
    }

    //расшифровка сообщения
    void decryptMessage() {
        cout << name << " расшифровывает сообщение." << endl;
        vector <string> vecstr;
        string word;
        stringstream s(cryptMes);

        while (s >> word) vecstr.push_back(word);

        long long int* arr = new long long int[vecstr.size()];


        for (int i = 0; i < vecstr.size(); i++) {
            arr[i] = stoi(vecstr[i]);
            arr[i] = Mod(arr[i], closeKey.a, n);
        }
        str = toChar(arr, str, vecstr.size());

        delete[] arr;
    }

    //вывод зашифрованного сообщения
    void showCrypt() {
        cout << name << " показывает зашифрованное сообщение: " << cryptMes << endl;
    }

    //вывод расшифрованного сообщения
    void showStr() {
        cout << name << " показывает расшифрованное сообщение: " << str << endl;
    }

    Human(string a) {
        name = a;
    }
};


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Human alise("Алиса");  //создание Алисы
    Human bob("Боб");      //создание Боба

    alise.createKey(); // Алиса создает ключи


    bob.getKey(alise);  //Боб берет у Алисы открытый ключ 
    bob.encryptMessage(); //Боб шифрует сообщение которое хочет отправить

    alise.getMes(bob);      //Алиса получает от боба зашифрованное сообщение
    alise.decryptMessage();  //Алиса расшифровывает сообщение скрытым ключем

    alise.showCrypt();    //Алиса показывает зашифрованное сообщение
    alise.showStr();      //Алиса показывает расшифрованное сообщение



}
