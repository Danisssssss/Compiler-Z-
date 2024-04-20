#include <iostream>
#include <fstream>      // ������ � ������� (������ � ������)
#include <sstream>      // �����, ���������� �� �������
#include <string>       
#include <stdexcept>    // ����������
#include <cstdlib>      // ���������� ������ ���������
#include <vector>

using namespace std;

// ��������� ��� �������� ���������� � ������ ������ ����
struct CodeLine {
    string line;
    int lineNumber;
};
int A = 0; // ������������� �������� �
vector<CodeLine> codeLines; // ������ ��� �������� ���������� � ������ ������ ����
string line;
int lineNumber = 1;

// ������� ��� ���������� ������� ADD
void add(int& A, int X, int Y) {
    A = X + Y;
}

// ������� ��� ���������� ������� MUL
void mul(int& A, int X, int Y) {
    A = X * Y;
}

// ������� ��� ������� ������ ������� � ���������� ��������������� ��������
void executeCommand(int& A, const string& command, int lineNumber) {
    stringstream ss(command);
    string operation, X_str, Y_str;

    ss >> operation; // ��������� ��������
    if (operation != "ADD" && operation != "MUL") {
        throw invalid_argument("������: ������������ ��������.");
    }

    char space;     // ���������� ��� �������� ����������� (�������)
    ss.get(space);  // ���� �������� ��������� ��������� ������ �� ������ ����� ss � ��������� ��� � ���������� space. 
                    // ��������� space ����� ��� char, get() ��������� ������ ���� ������ �� ������.
    if (space != ' ') {
        throw invalid_argument("������: ����������� ������ ����� �������� � ����������.");
    }

    getline(ss, X_str, ' '); // ��������� ������ �������
    if (X_str.empty() || isspace(X_str[0])) {
        throw invalid_argument("������: ����������� ������ �������.");
    }

    getline(ss, Y_str); // ��������� ������ ������� �� ����� ������
    if (Y_str.empty() || isspace(Y_str[0])) {
        throw invalid_argument("������: ����������� ������ �������.");
    }

    // ������� ������ ����� � ������� �� ������ Y_str
    if (!Y_str.empty() && Y_str[Y_str.size() - 1] == ';') {
        Y_str.pop_back();
    }
    else {
        throw invalid_argument("������: ������ �� ����������� ������ � �������.");
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
            throw invalid_argument("������: ������� ������� ������ �������.");
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
            throw invalid_argument("������: ������� ������� ������ �������.");
        }
    }

    char extra;
    if (ss >> extra) {
        throw invalid_argument("������: ����� ����� ������ ���� ������ �������.");
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
        cout << "�� ������� ������� ����." << endl;
        return 1;
    }

    ofstream outFile("result.txt");
    if (!outFile.is_open()) {
        cout << "�� ������� ������� ���� ��� ������ �����������." << endl;
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
                cout << "�������� �������� A ����� ���������� �������: " << A << endl; // � �������
                outFile << "�������� �������� A ����� ���������� �������: " << A << endl; // � ����
            }
            catch (const invalid_argument& e) {
                cout << e.what() << " � ������: " << codeLine.lineNumber << endl;
                outFile << e.what() << " � ������: " << codeLine.lineNumber << endl;
                return 1;
            }
        }
    }
    catch (const exception& e) {
        cout << "������: " << e.what() << endl;
        outFile << "������: " << e.what() << endl;
        return 1;
    }

    file.close();
    outFile.close();

    return 0;
}