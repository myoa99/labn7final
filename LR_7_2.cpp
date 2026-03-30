#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

double calc(string chislo, int osn, int proverka) {
	if (proverka == 1) { // из десятичной СИС
		int negative = 0, it = 0; // negative - проверка на отрицательное число,it - хранение индекса точки
		string inttobin = "", floattobin = "", invinttobin = ""; //inttobin-хранение целой части числа, floattobin - хранение части числа после точки, invinttobin - хранение инверсии после цикла перевода
		string alp{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' }; // Хранение алфавита
		string chislo1 = chislo; // chislo1 - изначальное число
		for (auto i : chislo1) { // цикл для нахождения индекса точки
			if (chislo1[it] == '.') {
				chislo1[it] = ',';
			}
			it++;
		}
		double chisl = stod(chislo1); // chisl - изначальное число переведенное в тип double
		if (chisl < 0) { //проверка на отрицательное число
			chisl = abs(chisl);
			negative++;
		}

		int cch = chisl, digit, sizecch = 0, sizedrobch = 0; // cch - хранение целой части числа, digit - хранение цифры для будущего цикла, sizecch - хранение размера целой части, sizedrobch - хранение размера дробной части
		double drobch = chisl - cch; // Хранение части числа после точки
		while (cch > 0) { // цикл для перевода целой части в сис с основанием osn
			digit = cch % osn;
			inttobin += alp[digit];
			cch /= osn;
			sizecch += 1;
		}
		for (int i = sizecch; i >= 0; i--) invinttobin += inttobin[i];// цикл для создание инверсии (полученного числа в ходе цикла перевода)
		while (drobch != 0) {  // цикл для перевода части числа после точки в СИС с основанием osn
			drobch *= osn;
			int cchast = static_cast<int>(drobch);
			floattobin += alp[cchast];
			drobch -= cchast;
			sizedrobch += 1;
			if (sizedrobch == 10)break; // регулировка кол-ва знаков после запятой
		};
		if (negative == 0) {
			if (sizecch == 0) {
				if (floattobin.empty()) cout << "Результат в " << osn << "-ичной СИС: 0" << endl;
				else cout << "Результат в " << osn << "-ичной СИС: 0." << floattobin << endl;
			}
			else if (sizedrobch == 0) cout << "Результат в " << osn << "-ичной СИС: " << invinttobin << endl;
			else cout << "Результат в " << osn << "-ичной СИС: " << invinttobin << '.' << floattobin << endl;
		}
		else { // для отрицательных чисел (аналогично, но с минусом)
			if (sizecch == 0) {
				if (floattobin.empty()) cout << "Результат в " << osn << "-ичной СИС: -0" << endl;
				else cout << "Результат в " << osn << "-ичной СИС: -0." << floattobin << endl;
			}
			else if (sizedrobch == 0) cout << "Результат в " << osn << "-ичной СИС: -" << invinttobin << endl;
			else cout << "Результат в " << osn << "-ичной СИС: -" << invinttobin << '.' << floattobin << endl;
		}
	}
	else { // в 10-ую СИС
		int negative = 0; // negative - проверка на отрицательное число
		string chis = chislo; // chis - исходное число
		if (chis[0] == '-') negative++; // проверка на отрицательное число
		string alp{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' }; // Создание алфавита
		int sizechislo = 0, tochka = 0, resint = 0, proverkatochka = 0; // sizechislo - хранение размера числа. tochka - хранение индекса точки. resint- хранение переведенной в 10 СИС целой части числа.proverkatochka-если 0, точки нет, если здесь будет 1, точка есть.
		double resfloat = 0.0, res = 0; // resfloat - хранение переведенной в 10 СИС части числа после точки. res - хранение итогового результата перевода.
		for (auto i : chis) {		// цикл для нахождения размера числа и здесь также проверка на точку
			sizechislo++;
			if (i == '.')proverkatochka++;
		}
		if (proverkatochka != 0) {// если есть точка, нахождение индекса точки
			while (chis[tochka] != '.') tochka++; // Нахождение индекса точки
		}
		else tochka = sizechislo;// если точки нету, индекс точки равен размеру числа
		for (int i = 0; i < tochka; i++) { // Работа с целой частью числа (до точки)
			for (int a = 0; a < 16; a++) // Цикл для работы с алфавитом
				if (chis[i] == alp[a]) resint += a * (pow(osn, (tochka - 1) - i)); // Перевод целой части числа в 10 СИС.
		}
		if (tochka != 0) { // Проверка на то, вещественное ли число
			for (int i = tochka + 1; i <= sizechislo - 1; i++) {// Работа с частью числа после точки
				for (int a = 0; a < 16; a++) {//Цикл для работы с алфавитом
					if (chis[i] == alp[a]) resfloat += a * (pow(osn, tochka - i));//Перевод части числа после точки в 10 СИС.
				}
			}
		}
		if (negative == 0) {// Нахождение результата если число положительное
			res = resint + resfloat;//Нахождение итогового результата
		}
		else res = -resint - resfloat;// Нахождение результата, если число отрицательное
		return res;
	}
}
int main()
{
	setlocale(LC_ALL, "RU");
	string chislo1, chislo2, res;//chislo1 - первое число, chislo2 - второе число, res- хранение результата операций с числами
	stringstream ss; // ss для будущего преобразования в строку
	int osn1, osn2, osn3; // osn1 - основание первого числа, osn2 - основание второго числа,osn3 - основание третьего числа,
	double res1, res2, res3; // res1 -хранение результата перевода первого числа, res2 -хранение результата перевода второго числа,res1 -хранение результата перевода операции с числами
	char op; // op - хранение операции
	cout << "Введите 1-ое число и его СИС[1-16]: " << endl;
	cin >> chislo1 >> osn1;// ввод первого числа и основания
	cout << "Введите 2-ое число и его СИС[1-16]: " << endl;
	cin >> chislo2 >> osn2;//ввод второго числа и основания
	cout << "Введите операцию(+ * - /):" << endl;
	cin >> op;// ввод операции
	cout << "Введите СИС[1-16], в котором хотите получить результат: " << endl;
	cin >> osn3;// ввод основания результата
	res1 = calc(chislo1, osn1, 0);//перевод первого числа
	res2 = calc(chislo2, osn2, 0);// перевод второго числа
	switch (op)// switch case для работы с операциями
	{
	case '+':
		res3 = res1 + res2;//нахождение результата операции с числами
		ss.str("");  // очищаем stream
		ss.clear();  // сбрасываем флаги
		ss << fixed << setprecision(10) << res3;
		res = ss.str();// перевод результата операции в строку
		calc(res, osn3, 1);
		break;
	case '*':
		res3 = res1 * res2;//нахождение результата операции с числами
		ss.str("");  // очищаем stream
		ss.clear();  // сбрасываем флаги
		ss << fixed << setprecision(10) << res3;
		res = ss.str();// перевод результата операции в строку
		calc(res, osn3, 1);
		break;
	case '-':
		res3 = res1 - res2;//нахождение результата операции с числами
		ss.str("");  // очищаем stream
		ss.clear();  // сбрасываем флаги
		ss << fixed << setprecision(10) << res3;
		res = ss.str();// перевод результата операции в строку
		calc(res, osn3, 1);
		break;
	case '/':
		if (res2 == 0) {// проверка на деление на 0
			cout << "Ошибка: деление на 0";
			return 0;
		}
		res3 = res1 / res2;//нахождение результата операции с числами
		ss.str("");  // очищаем stream
		ss.clear();  // сбрасываем флаги
		ss << fixed << setprecision(10) << res3;
		res = ss.str();// перевод результата операции в строку
		calc(res, osn3, 1);
		break;
	}
}