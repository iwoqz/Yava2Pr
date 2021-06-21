#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#pragma warning(disable : 4996)
#pragma warning(disable : 4703)

using namespace std;

class String {
private:
	static int k;
protected:
	void setString(char* fstring) {
		if (fstring == NULL) {
			cout << "Пустая строка" << endl;
			fstring = new char;
			fstring[0] = '\0';
		}
		else
			this->string = fstring;
	}

	void setLength(int flength) {
		this->length = flength;
	}

	char* string;
	int length;
public:
	String() {
		length = 0;
		string = new char[length + 1];
		string[0] = ' ';
		string[1] = '\0';
		cout << "Сработал конструктор без параметров класса String" << endl;
		getchar();
	}

	String(char* fstring) {
		string = new char[sizeof fstring];
		strcpy(string, fstring);
		length = strlen(string);
		cout << "Сработал конструктор с параметрами класса String" << endl;
	}

	String(String& other) {
		string = new char[sizeof other];
		static int k = 0;
		string = other.string;
		length = other.length;
		k++;
		cout << "Сработал конструктор копирования класса String" << k << "раз сработал" << endl;
	}

	~String() {
		if(string)
			delete[] string;
		cout << "Сработал деструктор класса String" << endl;
	}

	String& operator= (const String& fstring)
	{
		if (this->string != nullptr)
			delete[] string;
		length = strlen(fstring.string);
		this->string = new char[length + 1];
		for (int i = 0; i < length; i++)
			this->string[i] = fstring.string[i];
		this->string[length] = '\0';
		return *this;
	}

	char* getString() {
		return string;
	}

	int getLength() {
		return length;
	}

	ostream& operator<<(ostream& out) {
		if (string != NULL)
			out << string;
		else
			cout << "Строка пуста";
		return out;
	}

	istream& operator>>(istream& in) {
		cout << "Введите строку\n";
		in >> string;
		return in;
	}

	char &operator[] (const int index) {
		return string[index];
	}

};

class StringId :public String {
private:
	static int k;
public:
	StringId() {
		String();
		cout << "Сработал конструктор без параметров класса StringId" << endl;
	}

	StringId(char* sstring) {
		int k = 0;
		string = new char[sizeof sstring];
		while (k < strlen(sstring) && (isalpha(sstring[k]) || isdigit(sstring[k]) || sstring[k] == '_'))
			k++;
		if (k != strlen(sstring))
			return;
		strcpy(string, sstring);
		length = strlen(string);
		cout << "Сработал конструктор с параметрами класса StringId" << endl;
	}

	StringId(StringId& other) {
		static int k = 0;
		this->setString(other.getString());
		this->setLength(other.getLength());
		k++;
		cout << "Сработал конструктор копирования класса StringId" << k << "раз сработал" << endl;
	}

	~StringId() {
		cout << "Сработал деструктор класса StringId" << endl;
	}

	StringId& operator= (const StringId& sstring) {
		if (this->string != nullptr)
			delete[] string;
		length = strlen(sstring.string);
		this->string = new char[length+ 1];
		for (int i = 0; i < length; i++)
			this->string[i] = sstring.string[i];
		this->string[length] = '\0';
		return *this;
	}

	bool operator < (const StringId& sstring){
		if (strcmp(this->string, sstring.string) < 0) 
			return true;
		else 
			return false;
	}
};

class Complex :public String {
private:
	int real, image;
	static int k;
	
public:
	Complex() {
		String();
		real = 0;
		image = 0;
		cout << "Сработал конструктор без параметров класса Complex" << endl;
	}

	Complex(char* tstring) {
		this->string = new char[sizeof tstring];
		real = 0;
		image = 0;
		int k = 0, i = 0;
		bool sign = 0;
		char* number = new char[10];
		*number = NULL;
		while ((i < strlen(tstring)) && (isdigit(tstring[k]) || tstring[k] == 'i' || tstring[k] == '/' || tstring[k] == '!'))
			k++;
		if (k != strlen(tstring))
			return;
		k = 0;
		if (tstring[k] == '/')
			k++;
		else
			if (tstring[k] == '!') {
				sign = 1;
				k++;
			}
		while (tstring[k] != 'i' && isdigit(tstring[k ])) {
			number[k] = tstring[k];
			k++;
		}
		real = atoi(number);
		if (sign == 1)
			real = -real;
		for (int j = 0; j < k; j++)
			number[j] = NULL;
		k++;
		i = k;
		sign = 0;
		if (tstring[k] == '/') {
			k++;
			i++;
		}
		else
			if (tstring[k] == '!') {
				sign = 1;
				k++;
				i++;
			}
		while (k < strlen(tstring)) {
			number[k - 1] = tstring[k];
			k++;
		}
		image = atoi(number);
		if (sign == 1)
			image = -image;
		strcpy(string, tstring);
		length = strlen(string);
		cout << "Сработал конструктор с параметрами класса Complex" << endl;
	}

	Complex(Complex& other) {
		this->setString(other.getString());
		this->setLength(other.getLength());
		real = other.real;
		image = other.image;
		k++;
		cout << "Сработал конструктор копирования класса Coplex" << k << "раз сработал" << endl;
	}

	~Complex() {
		cout << "Сработал деструктор класса Complex" << endl;
	}

	Complex& operator= (const Complex& tstring) {
		if (this->string != nullptr)
			delete[] string;
		length = strlen(tstring.string);
		this->string = new char[length + 1];
		for (int i = 0; i < length; i++)
			this->string[i] = tstring.string[i];
		this->string[length] = '\0';
		return *this;
	}

	Complex& operator / (Complex& tstring) {
		char* tempReal = new char[10];
		char* tempImage = new char[10];
		int tReal = real;
		int tImage = image;
		real = tReal / tstring.real - tImage / tstring.image;
		image = tReal / tstring.image + tImage / tstring.real;
		_itoa_s(real, tempReal, 100, 10);
		strcat(tempReal, "k");
		_itoa_s(image, tempImage, 100, 10);
		strcat(tempReal, tempImage);
		this->setString(tempReal);
		this->setLength(strlen(tempReal));
		cout << this->getString() << endl;
		return *this;
	}
};

int main() {
	setlocale(LC_ALL, "Rus");
	char menu = 0;
	int n = 0, i = 0, k1 =0,  k2 = 0;
	String** strings;
	
	do {
		system("CLS");
		cout << "1. Инициализация" << endl;
		cout << "2. Тестирование" << endl;
		cout << "3.Выход" << endl;
		cin >> menu;

		switch (menu) {
		case '1':
			system("CLS");
			menu = 0;
			cout << "1. Число элементов" << endl;
			cout << "2. Начальное значение" << endl;
			cin >> menu;

			switch (menu) {
			case '1':
				if (n == 0) {
					cout << "Введите число элементов" << endl;
					cin >> n;
					strings = new String * [n];
				}
				else
					cout << "Число элементов уже введено" << endl;
				break;

			case '2':
				if (n == 0) {
					cout << "Число элементов ещё не введено, данный пункт меню недоступен" << endl;
					break;
				}
				i = 0;
				char* input = new char[100];
				while (i < n) {
					menu = 0;
					*input = NULL;
					cout << "Введите значение элемента №" << i + 1 << endl;
					getchar();
					gets_s(input, 100);
					cout << "Выберите значение элемента №" << i + 1 << endl;
					cout << "1. Строка" << endl;
					cout << "2. Строка-индентификатор" << endl;
					cout << "3. Комплексное число" << endl;
					cin >> menu;

					switch (menu) {
					case '1':
						strings[i] = new String(input);
						/*for (int j = 0; j < i + 1; j++)
							*strings[j] << cout << endl;*/
						break;
					case'2':
						strings[i] = new StringId(input);
						/*for (int j = 0; j < i + 1; j++)
							*strings[j] << cout << endl;*/
						break;
					case '3':
						strings[i] = new Complex(input);
						/*for (int j = 0; j < i + 1; j++)
							*strings[j] << cout << endl;*/
						break;

					default:
						strings[i] = new String();
						break;
					}
					menu = 0;
					i++;
				}
				break;
			}
			menu = 0;
			getchar();
			break;
		case '2':
			system("CLS");
			menu = 0;
			if (n == 0) {
				cout << "Число элементов ещё не введено, данный пункт меню не доступен" << endl;
				break;
			}
			cout << "1. Строка" << endl;
			cout << "2. Строка-идентификатор" << endl;
			cout << "3. Комплексное число" << endl;
			cout << "4. Задать операнды" << endl;
			cin >> menu;

			switch (menu) {
			case '1':
				system("CLS");
				cout << "1. Ввод элемента типа String" << endl;
				cout << "2. Вывод длины элемента типа String" << endl;
				cin >> menu;

				switch (menu) {
				case'1':
					i = 0;
					cout << "Введите номер элемента типа String" << endl;
					cin >> i;
					if ((i <= n) && (i > 0))
						*strings[i - 1] << cout;
					else
						cout << "Неверный номер элемеента";
					break;

				case '2':
					i = 0;
					cout << "Введите номер элемента типа String" << endl;
					cin >> i;
					if ((i <= n) && (i > 0))
						cout << strings[i - 1]->getLength();
					else
						cout << "Неверынй номер элемента";
					break;
				}
				menu = 0;
				getchar();
				break;
			case '2':
				system("CLS");
				menu = 0;
				cout << "1. Вывод элемента типа  StringId" << endl;
				cout << "2. Вывод длины элемента типа StringId" << endl;
				cin >> menu;

				switch (menu) {
				case '1':
					i = 0;
					cout << "Введите номер элемента типа StringId" << endl;
					cin >> i;
					if ((i <= n) && (i > 0))
						*strings[i - 1] << cout;
					else
						cout << "Неверный номер элемента";
					break;

				case '2':
					i = 0;
					cout << "Введите номер элемента типа StringId" << endl;
					cin >> i;
					if ((i <= n) && (i > 0))
						cout << strings[i - 1]->getLength();
					else
						cout << "Неверный номер элемента";
					break;
				}
				menu = 0;
				getchar();
				break;

			case '3':
				system("CLS");
				menu = 0;
				cout << "1. Вывод элемента типа Complex" << endl;
				cout << "2. Вывод длины элемента типа Comlex" << endl;
				cin >> menu;

				switch (menu) {
				case '1':
					i = 0;
					cout << "Введите номер элемента типа Complex" << endl;
					cin >> i;
					if ((i <= n) && (i > 0))
						*strings[i - 1] << cout;
					else
						cout << "Неверный номер элемента";
					break;

				case '2':
					i = 0;
					cout << "Введите номер элемента типа Complex" << endl;
					cin >> i;
					if ((i <= n) && (i > 0))
						cout << strings[i - 1]->getLength();
					else
						cout << "Неверный номер элемента";
					break;
				}
				menu = 0;
				getchar();
				break;

			case '4':
				system("CLS");
				menu = 0;
				cout << "1. Деление двух комплексных чисел типа Complex" << endl;
				cout << "2. Присвоение строке типа String знаечния другой строки типа String" << endl;
				cout << "3. Присвоение строке типа StringId знаечния другой строки типа StringId" << endl;
				cout << "4. Присвоение строке типа Complex знаечния другой строки типа Coplex" << endl;
				cin >> menu;

				switch (menu) {
				case '1':
					k1 = k2 = 0;
					cout << "Введите номер первой строки" << endl;
					cin >> k1;
					cout << "Введите номер второй строки" << endl;
					cin >> k2;
					*strings[k1 - 1] = *(Complex*)strings[k1 - 1] / *(Complex*)strings[k2 - 1];
					break;

				case '2':
					k1 = k2 = 0;
					cout << "Введите номер первой строки" << endl;
					cin >> k1;
					cout << "Введите номер второй строки" << endl;
					cin >> k2;
					*strings[k1 - 1] = *(String*)strings[k2 - 1];
					break;
					
				case '3':
					cout << "Введите номер первой строки" << endl;
					cin >> k1;
					cout << "Введите номер второй строки" << endl;
					cin >> k2;
					*strings[k1 - 1] = *(StringId*)strings[k2 - 1];
					break;

				case '4':
					cout << "Введите номер первой строки" << endl;
					cin >> k1;
					cout << "Введите номер второй строки" << endl;
					cin >> k2;
					*strings[k1 - 1] = *(Complex*)strings[k2 - 1];
					break;
				}
				menu = 0;
				getchar();
				break;
			}
			menu = 0;
			getchar();
			break;
		}
		getchar();
	}
	while (menu != '3');
}
