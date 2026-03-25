#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "rus");
    auto toDecimal = [](const string& numStr, int base) -> int {
        int value = 0;
        for (char c : numStr) {
            if (isdigit(c))
                value = value * base + (c - '0');
            else if (isalpha(c))
                value = value * base + (toupper(c) - 'A' + 10);
            else
                throw invalid_argument("Некорректный символ");
        }
        return value;
        };

    auto fromDecimal = [](int num, int base) -> string {
        if (num == 0) return "0";

        string result;
        bool isNegative = false;
        if (num < 0) {
            isNegative = true;
            num = -num;
        }

        while (num > 0) {
            int rem = num % base;
            if (rem < 10)
                result += ('0' + rem);
            else
                result += ('A' + rem - 10);
            num /= base;
        }

        if (isNegative)
            result += '-';

        reverse(result.begin(), result.end());
        return result;
        };

    auto selectBase = [](const string& prompt) -> int {
        int base;
        while (true) {
            cout << prompt;
            cin >> base;
            if (base == 2 || base == 8 || base == 10 || base == 16)
                break;
            cout << "Пожалуйста, выберите систему счисления: 2, 8, 10 или 16.\n";
        }
        return base;
        };

    auto inputNumber = [](const string& prompt, int base) -> string {
        string numStr;
        while (true) {
            cout << prompt;
            cin >> numStr;
            bool valid = true;
            for (size_t i = 0; i < numStr.size(); ++i) {
                char c = numStr[i];
                if (c == '-' && i == 0) continue;
                if (isdigit(c))
                    if ((c - '0') >= base) { valid = false; break; }
                    else if (isalpha(c))
                        if ((toupper(c) - 'A' + 10) >= base) { valid = false; break; }
                        else {
                            valid = false; break;
                        }
            }
            if (valid && !numStr.empty())
                break;
            cout << "Некорректный ввод для системы " << base << ". Попробуйте снова.\n";
        }
        return numStr;
        };

    auto selectOperation = []() -> char {
        char op;
        while (true) {
            cout << "Выберите операцию (+, -, *, /): ";
            cin >> op;
            if (op == '+' || op == '-' || op == '*' || op == '/')
                break;
            cout << "Некорректная операция. Попробуйте снова.\n";
        }
        return op;
        };

    cout << "Калькулятор для различных систем счисления\n";

    // Ввод первого числа
    int base1 = selectBase("Выберите систему счисления для первого числа (2, 8, 10, 16): ");
    string numStr1 = inputNumber("Введите первое число: ", base1);
    int num1 = toDecimal(numStr1, base1);

    // Ввод второго числа
    int base2 = selectBase("Выберите систему счисления для второго числа (2, 8, 10, 16): ");
    string numStr2 = inputNumber("Введите второе число: ", base2);
    int num2 = toDecimal(numStr2, base2);

    // Выбор операции
    char op;
    while (true) {
        cout << "Выберите операцию (+, -, *, /): ";
        cin >> op;
        if (op == '+' || op == '-' || op == '*' || op == '/')
            break;
        cout << "Некорректная операция. Попробуйте снова.\n";
    }

    // Выполнение операции
    if (op == '/' && num2 == 0) {
        cout << "Ошибка: деление на ноль!\n";
        return 0;
    }

    int result;
    switch (op) {
    case '+': result = num1 + num2; break;
    case '-': result = num1 - num2; break;
    case '*': result = num1 * num2; break;
    case '/': result = num1 / num2; break;
    }

    // Выбор системы счисления для вывода
    int resultBase = selectBase("Выберите систему счисления для результата (2, 8, 10, 16): ");

    // Вывод результата
    string resultStr;
    if (result >= 0)
        resultStr = fromDecimal(result, resultBase);
    else {
        resultStr = "-" + fromDecimal(-result, resultBase);
    }
    cout << "Результат: " << resultStr << " (в системе " << resultBase << ")\n";

    return 0;
}