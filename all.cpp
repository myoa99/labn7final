#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    string chislo1, chislo2, res;
    int osn1, osn2, osn3;
    double res1, res2, res3;
    char op;

    cout << "Введите 1-ое число и его СИС[1-16]: " << endl;
    cin >> chislo1 >> osn1;
    cout << "Введите 2-ое число и его СИС[1-16]: " << endl;
    cin >> chislo2 >> osn2;
    cout << "Введите операцию(+ * - /):" << endl;
    cin >> op;
    cout << "Введите СИС[1-16], в котором хотите получить результат: " << endl;
    cin >> osn3;

    // --- Обработка первого числа (из любой системы в десятичную) ---
    {
        int negative = 0;
        string chis = chislo1;
        if (chis[0] == '-') { negative = 1; chis.erase(0,1); }

        string alp{ "0123456789ABCDEF" };
        int sizechislo = chis.size();
        int tochka = -1;
        for (int i = 0; i < sizechislo; ++i) {
            if (chis[i] == '.') { tochka = i; break; }
        }
        if (tochka == -1) tochka = sizechislo;

        int resint = 0;
        for (int i = 0; i < tochka; ++i) {
            int digit = alp.find(toupper(chis[i]));
            if (digit == -1) continue;
            resint = resint * osn1 + digit;
        }

        double resfloat = 0.0;
        double divisor = osn1;
        for (int i = tochka + 1; i < sizechislo; ++i) {
            int digit = alp.find(toupper(chis[i]));
            if (digit == -1) continue;
            resfloat += digit / divisor;
            divisor *= osn1;
        }

        res1 = resint + resfloat;
        if (negative) res1 = -res1;
    }

    // --- Обработка второго числа (из любой системы в десятичную) ---
    {
        int negative = 0;
        string chis = chislo2;
        if (chis[0] == '-') { negative = 1; chis.erase(0,1); }

        string alp{ "0123456789ABCDEF" };
        int sizechislo = chis.size();
        int tochka = -1;
        for (int i = 0; i < sizechislo; ++i) {
            if (chis[i] == '.') { tochka = i; break; }
        }
        if (tochka == -1) tochka = sizechislo;

        int resint = 0;
        for (int i = 0; i < tochka; ++i) {
            int digit = alp.find(toupper(chis[i]));
            if (digit == -1) continue;
            resint = resint * osn2 + digit;
        }

        double resfloat = 0.0;
        double divisor = osn2;
        for (int i = tochka + 1; i < sizechislo; ++i) {
            int digit = alp.find(toupper(chis[i]));
            if (digit == -1) continue;
            resfloat += digit / divisor;
            divisor *= osn2;
        }

        res2 = resint + resfloat;
        if (chis[0] == '-') res2 = -res2;
    }

    switch (op)
    {
        case '+':
            res3 = res1 + res2;
            break;
        case '-':
            res3 = res1 - res2;
            break;
        case '*':
            res3 = res1 * res2;
            break;
        case '/':
            if (res2 == 0) {
                cout << "Ошибка: деление на 0" << endl;
                return 0;
            }
            res3 = res1 / res2;
            break;
        default:
            cout << "Некорректная операция" << endl;
            return 0;
    }

    // --- Перевод результата из десятичной в нужную систему ---
    stringstream ss;
    ss << fixed << setprecision(15) << res3;
    string resStr = ss.str();

    // Обработка результата в системе osn3
    {
        int negative = 0;
        string chis = resStr;
        if (!chis.empty() && chis[0] == '-') { negative = 1; chis.erase(0,1); }

        string alp{ "0123456789ABCDEF" };
        int sizechislo = chis.size();
        int tochka = -1;
        for (int i = 0; i < sizechislo; ++i) {
            if (chis[i] == '.') { tochka = i; break; }
        }
        if (tochka == -1) tochka = sizechislo;

        // Обработка целой части
        int resint = 0;
        for (int i = 0; i < tochka; ++i) {
            int digit = alp.find(toupper(chis[i]));
            if (digit == -1) continue;
            resint = resint * osn3 + digit;
        }

        // Обработка дробной части
        double fractional = 0.0;
        if (tochka != -1 && tochka + 1 < sizechislo) {
            double divisor = osn3;
            for (int i = tochka + 1; i < sizechislo; ++i) {
                int digit = alp.find(toupper(chis[i]));
                if (digit == -1) continue;
                fractional += digit / divisor;
                divisor *= osn3;
            }
        }

        // Итоговая строка
        string resultStr;
        if (negative) resultStr = "-";

        // Конвертация целой части в строку
        stringstream ssInt;
        ssInt << resint;
        resultStr += ssInt.str();

        // Добавляю дробную часть, если есть
        if (fractional > 1e-12) {
            resultStr += ".";
            // Форматируем дробную часть как строку
            int max_digits = 15; // количество знаков после запятой
            double frac_part = fractional;
            for (int i = 0; i < max_digits; ++i) {
                frac_part *= osn3;
                int digit = static_cast<int>(frac_part);
                resultStr += alp[digit];
                frac_part -= digit;
                if (frac_part < 1e-12) break;
            }
        }

        cout << "Результат в " << osn3 << "-ичной СИС: " << resultStr << endl;
    }

    return 0;
}