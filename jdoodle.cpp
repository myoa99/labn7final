#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// Преобразует число в виде строки из системы счисления в десятичное число
int toDecimal(const string& numStr, int base) {
    int value = 0;
    for(char c : numStr) {
        if (isdigit(c))
            value = value * base + (c - '0'); // цифры 0-9
        else if (isalpha(c))
            value = value * base + (toupper(c) - 'A' + 10); // буквы A-F
        else
            throw invalid_argument("Некорректный символ");
    }
    return value;
}

// Преобразует десятичное число в строку в выбранной системе счисления
string fromDecimal(int num, int base) {
    if (num == 0) return "0"; // случай нуля

    string result;
    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num = -num; // Обрабатываем отрицательное число
    }

    // Получаем разряды числа
    while (num > 0) {
        int rem = num % base; // остаток
        if (rem < 10)
            result += ('0' + rem); // цифры 0-9
        else
            result += ('A' + rem - 10); // буквы A-F
        num /= base;
    }

    if (isNegative)
        result += '-'; // Добавляем знак минус для отрицательных чисел

    reverse(result.begin(), result.end()); // Разворачиваем строку
    return result;
}

// Ввод числа с проверкой корректности для выбранной системы счисления
string inputNumber(const string& prompt, int base) {
    string numStr;
    while (true) {
        cout << prompt;
        cin >> numStr;
        // Проверка каждого символа
        bool valid = true;
        for (char c : numStr) {
            if (c == '-' && &c == &numStr[0]) continue; // минус только в начале
            if (isdigit(c))
                if ((c - '0') >= base) {
                    valid = false; // цифра недопустима для базы
                    break;
                }
            else if (isalpha(c))
                if ((toupper(c) - 'A' + 10) >= base) {
                    valid = false; // буква недопустима для базы
                    break;
                }
            else {
                valid = false; // недопустимый символ
                break;
            }
        }
        if (valid && !numStr.empty())
            break; // ввод корректен
        cout << "Некорректный ввод для системы " << base << ". Попробуйте снова.\n";
    }
    return numStr;
}

// Выбор системы счисления
int selectBase(const string& prompt) {
    int base;
    while (true) {
        cout << prompt;
        cin >> base;
        if (base == 2 || base == 8 || base == 10 || base == 16)
            break; // допустимые значения
        cout << "Пожалуйста, выберите систему счисления: 2, 8, 10 или 16.\n";
    }
    return base;
}

// Выбор операции
char selectOperation() {
    char op;
    while (true) {
        cout << "Выберите операцию (+, -, *, /): ";
        cin >> op;
        if (op == '+' || op == '-' || op == '*' || op == '/')
            break; // допустимые операции
        cout << "Некорректная операция. Попробуйте снова.\n";
    }
    return op;
}

int main() {
    cout << "Калькулятор для различных систем счисления\n";

    // Ввод первого числа
    int base1 = selectBase("Выберите систему счисления для первого числа (2, 8, 10, 16): ");
    string numStr1 = inputNumber("Введите первое число: ", base1);
    int num1 = toDecimal(numStr1, base1); // перевод в десятичное

    // Ввод второго числа
    int base2 = selectBase("Выберите систему счисления для второго числа (2, 8, 10, 16): ");
    string numStr2 = inputNumber("Введите второе число: ", base2);
    int num2 = toDecimal(numStr2, base2); // перевод в десятичное

    // Выбор операции
    char op = selectOperation();

    // Выполнение операции
    int result;
    if (op == '/' && num2 == 0) {
        cout << "Ошибка: деление на ноль!\n";
        return 1; // завершение при делении на ноль
    }

    switch(op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
    }

    // Выбор системы счисления для вывода результата
    int resultBase = selectBase("Выберите систему счисления для результата (2, 8, 10, 16): ");

    // Вывод результата
    string resultStr = fromDecimal(result, resultBase);
    cout << "Результат: " << resultStr << " (в системе " << resultBase << ")\n";

    return 0;
}