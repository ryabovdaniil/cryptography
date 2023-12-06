#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <vector>

using namespace std;

const char arr[45]{ ' ', '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','0','1','2','3','4','5','6','7','8','9' };

//�������� �� �� ������� �� �����
bool simple(int n) {
    for (int i = 2; i <= n / 2; i++) if ((n % i) == 0) return false;
    return true;
}

//������� �������� ��������� � �������� ��������
void toNumber(string str, long long int* arr1) {
    for (int i = 0; i < str.length(); i++) {
        for (int j = 0; j < 44; j++) {
            if (str[i] == arr[j]) { arr1[i] = j; continue; }
        }
    }

}

//������� ����� � �������
string toChar(long long int* arr1, string str, int n) {
    str.resize(n);
    for (int i = 0; i < n; i++) {
        str[i] = arr[arr1[i]];
    }
    return str;
}

//������� ���������� ������� ����� �� ������ n
long long int Mod(int x, int step, int mod) {
    long long int res = 1;
    for (int i = 0; i < step; i++) {
        res = (res * x) % mod;
    }
    return res;
}

//��������� �����
struct Key {
    int a;
    int b;
    // ���������� ��������� ����������
    Key operator = (Key key1) {
        a = key1.a;
        b = key1.b;
        return *this;
    }



};

//����� �������� 
class Human {
    string str;       //���������
    string cryptMes;  //������������� ���������
    int p = 0;
    int q = 0;
    int n = 0;
    Key openKey;      //�������� ����
    Key closeKey;     //�������� ����
public:
    string name;      //��� ��������

    // ����� ��� ������� �������� p � q
    void getPQ() {
        cout << "p � q ������ ���� ��������." << endl;
        cout << "������� p: ";
        cin >> p;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << "������� q: ";
        cin >> q;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
    }

    // ����� �������� ��������� � ��������� �����
    void createKey() {
        cout << name << " ������� �������� � �������� �����." << endl;
        getPQ();
        n = p * q;
        int f = (p - 1) * (q - 1);
        int e = 0;
        for (int i = 2; i < f; i++)  if (simple(i) && f % i != 0) { e = i; break; }  //���������� ��������� �����
        openKey.a = e;
        openKey.b = n;

        //���������� ��������� �����
        int d = 0;
        for (int i = 2; i < n; i++) {
            if ((i * e) % f == 1) { d = i; }
        }
        closeKey.a = d;
        closeKey.b = n;

        cout << "�������� ����: {" << openKey.a << "," << openKey.b << "}" << endl;
        cout << "�������� ����: {" << closeKey.a << "," << closeKey.b << "}" << endl;

    }

    //����� ��������� ��������� ����� �� ������� ��������
    void getKey(Human f) {
        cout << name << " ����� �������� ���� � " << f.name << endl;
        openKey = f.pushKey();
        n = openKey.b;
        cout << "{" << openKey.a << "," << openKey.b << "}" << endl;
    }

    //����� ��� ���� ����� ������ �������� ����
    Key pushKey() {
        return openKey;
    }

    // ���������� ���������
    void encryptMessage() {

        cout << "������� ���������" << endl;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        getline(cin, str);
        cin.ignore(cin.rdbuf()->in_avail(), '\n');

        cout << name << " ������� ��������� ���������� �������� ������." << endl;
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

    //����� ��� ���� ����� ������ ������������� ��������� ������� ��������
    string sendMess() {
        return cryptMes;
    }

    //����� ��� ��������� �� �������� �������������� ���������
    void getMes(Human f) {
        cout << name << " �������� ������������� ��������� �� " << f.name << endl;
        cryptMes = f.sendMess();
    }

    //����������� ���������
    void decryptMessage() {
        cout << name << " �������������� ���������." << endl;
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

    //����� �������������� ���������
    void showCrypt() {
        cout << name << " ���������� ������������� ���������: " << cryptMes << endl;
    }

    //����� ��������������� ���������
    void showStr() {
        cout << name << " ���������� �������������� ���������: " << str << endl;
    }

    Human(string a) {
        name = a;
    }
};


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Human alise("�����");  //�������� �����
    Human bob("���");      //�������� ����

    alise.createKey(); // ����� ������� �����


    bob.getKey(alise);  //��� ����� � ����� �������� ���� 
    bob.encryptMessage(); //��� ������� ��������� ������� ����� ���������

    alise.getMes(bob);      //����� �������� �� ���� ������������� ���������
    alise.decryptMessage();  //����� �������������� ��������� ������� ������

    alise.showCrypt();    //����� ���������� ������������� ���������
    alise.showStr();      //����� ���������� �������������� ���������



}
