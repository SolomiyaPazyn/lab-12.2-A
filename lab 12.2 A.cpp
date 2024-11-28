#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

enum Majors { RI = 1, IK, PZ, AI, KN, SA }; // Перелічуваний тип для спеціальностей
enum Subjects { Physics = 1, Math, IT };   // Перелічуваний тип для предметів

#pragma pack(push, 1)
struct Student {
    char prizv[50];             // Прізвище студента
    unsigned short course;      // Курс
    Majors major;               // Спеціальність
    unsigned short physics;     // Оцінка з фізики
    unsigned short math;        // Оцінка з математики
    unsigned short it;          // Оцінка з інформатики

    string return_major() {
        // Повертає назву спеціальності у вигляді рядка
        switch (this->major) {
        case RI: return "RI";
        case IK: return "IK";
        case PZ: return "PZ";
        case AI: return "AI";
        case KN: return "KN";
        case SA: return "SA";
        }
    }

    void fill_class(int i) {
        // Заповнює дані для одного студента
        int temp;
        cout << "Студент №" << i + 1 << endl;
        cout << "Прізвище: "; cin >> ws; cin.getline(this->prizv, 50);
        cout << "Курс: "; cin >> this->course;
        cout << "Спеціальність (RI=1, IK=2, PZ=3, AI=4, KN=5, SA=6): "; cin >> temp;
        this->major = (Majors)temp;
        cout << "Оцінка з фізики: "; cin >> this->physics;
        cout << "Оцінка з математики: "; cin >> this->math;
        cout << "Оцінка з інформатики: "; cin >> this->it;
    }
};
#pragma pack(pop)

// Записує масив студентів у бінарний файл
void writeStudentsToFile(Student* arr, int n, const char* filename) {
    ofstream file(filename, ios::binary); //відкриває файл для запису даних у бінарному режимі.
    if (!file) {
        cerr << "Error opening file for writing" << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        file.write((char*)(&arr[i]), sizeof(Student));
    }
    file.close();
}

// Зчитує масив студентів із бінарного файлу
void readStudentsFromFile(Student* arr, int n, const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading" << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        file.read((char*)(&arr[i]), sizeof(Student));
    }
    file.close();
}

// Обчислює відсоток студентів-відмінників
float calculateExcellentStudentsPercentage(const char* filename, int n) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading" << endl;
        exit(1);
    }
    Student s;
    int excellentCount = 0;
    for (int i = 0; i < n; i++) {
        file.read((char*)(&s), sizeof(Student));
        if (s.physics == 5 && s.math == 5 && s.it == 5) {
            excellentCount++;
        }
    }
    file.close();
    return (float)excellentCount / n * 100;
}

// Виводить список студентів, які отримали 5 з фізики
void printStudentsWithExcellentPhysics(const char* filename, int n) {
    ifstream file(filename, ios::binary); //відкриває файл у режимі читання
    if (!file) {
        cerr << "Error opening file for reading" << endl;
        exit(1);
    }
    Student s;
    bool found = false;
    cout << "Студенти, які отримали 5 з фізики:" << endl;
    for (int i = 0; i < n; i++) {
        file.read((char*)(&s), sizeof(Student));
        if (s.physics == 5) {
            cout << i + 1 << ". " << s.prizv << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Таких студентів немає" << endl;
    }
    file.close();
}

// Заповнює масив студентів і записує їх у файл
void fill_arr(Student* arr, int n, const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for writing" << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        arr[i].fill_class(i);
        file.write((char*)(&arr[i]), sizeof(Student));
    }
    file.close();
}

// Підраховує кількість цифр у числі (для форматування таблиці)
int calc_n(int n) {
    int res = 0;
    while (n != 0) {
        n /= 10;
        res++;
    }
    return res;
}

// Знаходить довжину найдовшого прізвища серед студентів
int lenOfLongestPrizv(const char* filename, int n) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading" << endl;
        exit(1);
    }
    Student s;
    int res = -1;
    for (int i = 0; i < n; i++) {
        file.read((char*)(&s), sizeof(Student));
        if ((int)(strlen(s.prizv)) > res) {
            res = (int)(strlen(s.prizv));
        }
    }
    file.close();
    return res;
}

// Виводить заголовок таблиці та дані студентів
void printHeader(const char* filename, int n) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading" << endl;
        exit(1);
    }
    Student s;
    int width = lenOfLongestPrizv(filename, n);
    (width <= 8) ? (width = 8) : (NULL);
    int maxDigits = calc_n(n);

    // Виведення заголовка таблиці
    cout << "=======================================================================";
    for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
        cout << "=";
    }
    cout << endl;

    cout << "|" << setw(maxDigits) << right << "№";
    cout << "|" << setw(width) << left << "Прізвище" << "| Курс | Спеціальність | Фізика | Математика | Інформатика | " << endl;

    cout << "-----------------------------------------------------------------------";
    for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
        cout << "-";
    }
    cout << endl;

    // Виведення даних студентів
    for (int i = 0; i < n; i++) {
        file.read((char*)(&s), sizeof(Student));
        cout << "|" << setw(maxDigits) << right << i + 1;
        cout << "|" << setw(width) << left << s.prizv;
        cout << "|" << setw(6) << left << s.course;
        cout << "|" << setw(15) << left << s.return_major();
        cout << "|" << setw(8) << left << s.physics;
        cout << "|" << setw(12) << left << s.math;
        cout << "|" << setw(13) << left << s.it;
        cout << setw(13) << "|" << endl;
    }

    cout << "-----------------------------------------------------------------------";
    for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
        cout << "-";
    }
    cout << endl;
    file.close();
}

int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 
    int n;
    cout << "Введіть кількість студентів: "; cin >> n;

    Student* arr = new Student[n]; // Динамічне створення масиву студентів

    char filename[100];
    cout << "Введіть ім'я файлу: "; cin >> filename;

    fill_arr(arr, n, filename); // Заповнення масиву та запис у файл

    printHeader(filename, n); 

    cout << fixed << setprecision(2);
    cout << "Процент студентів-відмінників: " << calculateExcellentStudentsPercentage(filename, n) << "%" << endl << endl;
    printStudentsWithExcellentPhysics(filename, n); 

    delete[] arr; 
    return 0;
}
