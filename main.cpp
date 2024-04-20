#include <iostream>
#include <fstream>      // работа с файлами (чтение и запись)
#include <sstream>      // поток, работающий со строкой
#include <string>       
#include <stdexcept>    // исключения
#include <cstdlib>      // завершение работы программы
#include <vector>

using namespace std;

// Структура для хранения информации о каждой строке кода
struct CodeLine {
    string line;
    int lineNumber;
};
int A = 0; // Инициализация регистра А
vector<CodeLine> codeLines; // Вектор для хранения информации о каждой строке кода
string line;
int lineNumber = 1;

// Функция для выполнения команды ADD
void add(int& A, int X, int Y) {
    A = X + Y;
}

// Функция для выполнения команды MUL
void mul(int& A, int X, int Y) {
    A = X * Y;
}

// Функция для разбора строки команды и выполнения соответствующей операции
void executeCommand(int& A, const string& command, int lineNumber) {
    stringstream ss(command);
    string operation, X_str, Y_str;

    ss >> operation; // Считываем операцию
    if (operation != "ADD" && operation != "MUL") {
        throw invalid_argument("Ошибка: Некорректная операция.");
    }

    char space;     // Переменная для хранения разделителя (пробела)
    ss.get(space);  // Этот оператор считывает следующий символ из потока ввода ss и сохраняет его в переменную space. 
                    // Поскольку space имеет тип char, get() считывает только один символ из потока.
    if (space != ' ') {
        throw invalid_argument("Ошибка: Отсутствует пробел между командой и операндами.");
    }

    getline(ss, X_str, ' '); // Считываем первый операнд
    if (X_str.empty() || isspace(X_str[0])) {
        throw invalid_argument("Ошибка: Отсутствует первый операнд.");
    }

    getline(ss, Y_str); // Считываем второй операнд до конца строки
    if (Y_str.empty() || isspace(Y_str[0])) {
        throw invalid_argument("Ошибка: Отсутствует второй операнд.");
    }

    // Удаляем символ точки с запятой из строки Y_str
    if (!Y_str.empty() && Y_str[Y_str.size() - 1] == ';') {
        Y_str.pop_back();
    }
    else {
        throw invalid_argument("Ошибка: Строка не завершается точкой с запятой.");
    }

    int X, Y;
    if (X_str == "A") {
        X = A;
    }
    else {
        try {
            X = stoi(X_str);
        }
        catch (const invalid_argument& e) {
            throw invalid_argument("Ошибка: Неверно написан первый операнд.");
        }
    }
    if (Y_str == "A") {
        Y = A;
    }
    else {
        try {
            Y = stoi(Y_str);
        }
        catch (const invalid_argument& e) {
            throw invalid_argument("Ошибка: Неверно написан второй операнд.");
        }
    }

    char extra;
    if (ss >> extra) {
        throw invalid_argument("Ошибка: После конца строки есть лишние символы.");
    }

    if (operation == "ADD") {
        add(A, X, Y);
    }
    else if (operation == "MUL") {
        mul(A, X, Y);
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    ifstream file("code.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }

    ofstream outFile("result.txt");
    if (!outFile.is_open()) {
        cout << "Не удалось создать файл для записи результатов." << endl;
        return 1;
    }

    while (getline(file, line)) {
        codeLines.push_back({ line, lineNumber });
        lineNumber++;
    }

    try {
        for (const auto& codeLine : codeLines) {
            try {
                executeCommand(A, codeLine.line, codeLine.lineNumber);
                cout << "Значение регистра A после выполнения команды: " << A << endl; // в консоль
                outFile << "Значение регистра A после выполнения команды: " << A << endl; // в файл
            }
            catch (const invalid_argument& e) {
                cout << e.what() << " В строке: " << codeLine.lineNumber << endl;
                outFile << e.what() << " В строке: " << codeLine.lineNumber << endl;
                return 1;
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        outFile << "Ошибка: " << e.what() << endl;
        return 1;
    }

    file.close();
    outFile.close();

    return 0;
}