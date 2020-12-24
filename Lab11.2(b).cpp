/*
Обчислити кількість кожної з оцінок «5», «4», «3» з фізики
Обчислити кількість студентів, які отримали і з фізики і з математики оцінки «4» або «5»
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum Specialty { KN, INF, ME, PI, TD };

string specialtyStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та екноміка", " Фізика та інформатика", "Трудове навчання" };

struct Student {
    char prizv[64];
    unsigned kurs;
    Specialty specialty;
    unsigned gradePhys;
    int gradeMath;
    union {
        unsigned gradeProg;
        unsigned gradeMetod;
        unsigned gradePed;
    };
};



void Create(const char* fName)
{
    ofstream f(fName, ios::binary);
    Student student;
    char ch;
    int specialty;
    do {

        cout << "Прізвище: ";
        cin >> student.prizv;
        cout << "Курс: "; cin >> student.kurs;
        cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та екноміка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> specialty;
        student.specialty = (Specialty)specialty;
        cout << "Оцінка з фізики: "; cin >> student.gradePhys;
        cout << "Оцінка з математики: "; cin >> student.gradeMath;
        switch (student.specialty) {
        case KN:
            cout << "Оцінка з програмування: "; cin >> student.gradeProg;
            break;
        case INF:
            cout << "Оцінка з чисельних методоів: "; cin >> student.gradeMetod;
            break;
        default:
            cout << "Оцінка педагогіки: "; cin >> student.gradePed;
            break;
        }

        cout << endl;
        if (!f.write((char*)&student, sizeof(Student))) {
            cerr << "Error writing file." << endl;
        }
        cout << "Continue?(Y/N)"; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}


void Print(const char* fName)
{
    cout << endl << "\nfile \"" << fName << "\":\n";
    cout << "====================================================================================================================================================================================================" << endl;
    cout << "|  No  |    Прізвище    |  Курс  |      Спеціальність      |   Оцінка з фізкики   |   Оцінка з математики   |   Оцінка з програмування   |   Оцінка з чисельних методоів   |   Оцінка педагогіки   |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    ifstream f(fName, ios::binary);
    Student student;
    int i = 1;
    while (f.read((char*)&student, sizeof(Student))) {
        cout << "| " << setw(3) << right << i++ << "  ";
        cout << "| " << setw(15) << left << student.prizv
            << "|   " << setw(3) << right << student.kurs << "  "
            << "| " << setw(24) << left << specialtyStr[student.specialty]
            << "| " << setw(20) << right << student.gradePhys << " "
            << "| " << setw(23) << right << student.gradeMath << " ";
        switch (student.specialty) {
        case KN:
            cout << "| " << setw(26) << fixed << right << student.gradeProg
                << " |" << setw(34) << "|" << setw(24) << "|" << endl;
            break;
        case INF:
            cout << "|" << setw(30)
                << "| " << right << fixed << setw(31) << student.gradeMetod << " |" << setw(24) << "|" << endl;
            break;
        default:
            cout << "|" << setw(29)
                << "|" << setw(35) << "| " << setw(21) << student.gradePed << " |" << endl;
            break;
        }

    }
    cout << "====================================================================================================================================================================================================" << endl;
    cout << endl;
}


void physStat(const char* fName, int& threeCount, int& fourCount, int& fiveCount) {
    ifstream f(fName, ios::binary);
    Student student;
    while (f.read((char*)&student, sizeof(Student))) {
        if (student.gradePhys == 3) {
            threeCount++;
        }
        else if (student.gradePhys == 4) {
            fourCount++;
        }
        else if (student.gradePhys == 5) {
            fiveCount++;
        }

    }
}

int goodMathPhys(const char* fName) {
    int n = 0;
    ifstream f(fName, ios::binary);
    Student student;
    while (f.read((char*)&student, sizeof(Student))) {
        if ((student.gradeMath == 4 || student.gradeMath == 5) && (student.gradePhys == 4 || student.gradePhys == 5))
            n++;

    }
    return n;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int threeCount = 0, fourCount = 0, fiveCount = 0;

    char f[6] = "f.dat";
    Create(f);
    Print(f);

    physStat(f, threeCount, fourCount, fiveCount);

    cout << "Кількість 3 за фізику: " << threeCount << endl;
    cout << "Кількість 4 за фізику: " << fourCount << endl;
    cout << "Кількість 5 за фізику: " << fiveCount << endl;

    cout << "Кількість учнів із заданим критерієм: " << goodMathPhys(f) << endl;

    system("pause");
    cin.get();
    return 0;
}

