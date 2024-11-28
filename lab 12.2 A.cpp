#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

enum Majors { RI = 1, IK, PZ, AI, KN, SA }; // ������������ ��� ��� ��������������
enum Subjects { Physics = 1, Math, IT };   // ������������ ��� ��� ��������

#pragma pack(push, 1)
struct Student {
    char prizv[50];             // ������� ��������
    unsigned short course;      // ����
    Majors major;               // ������������
    unsigned short physics;     // ������ � ������
    unsigned short math;        // ������ � ����������
    unsigned short it;          // ������ � �����������

    string return_major() {
        // ������� ����� ������������ � ������ �����
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
        // �������� ��� ��� ������ ��������
        int temp;
        cout << "������� �" << i + 1 << endl;
        cout << "�������: "; cin >> ws; cin.getline(this->prizv, 50);
        cout << "����: "; cin >> this->course;
        cout << "������������ (RI=1, IK=2, PZ=3, AI=4, KN=5, SA=6): "; cin >> temp;
        this->major = (Majors)temp;
        cout << "������ � ������: "; cin >> this->physics;
        cout << "������ � ����������: "; cin >> this->math;
        cout << "������ � �����������: "; cin >> this->it;
    }
};
#pragma pack(pop)

// ������ ����� �������� � ������� ����
void writeStudentsToFile(Student* arr, int n, const char* filename) {
    ofstream file(filename, ios::binary); //������� ���� ��� ������ ����� � �������� �����.
    if (!file) {
        cerr << "Error opening file for writing" << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        file.write((char*)(&arr[i]), sizeof(Student));
    }
    file.close();
}

// ����� ����� �������� �� �������� �����
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

// �������� ������� ��������-��������
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

// �������� ������ ��������, �� �������� 5 � ������
void printStudentsWithExcellentPhysics(const char* filename, int n) {
    ifstream file(filename, ios::binary); //������� ���� � ����� �������
    if (!file) {
        cerr << "Error opening file for reading" << endl;
        exit(1);
    }
    Student s;
    bool found = false;
    cout << "��������, �� �������� 5 � ������:" << endl;
    for (int i = 0; i < n; i++) {
        file.read((char*)(&s), sizeof(Student));
        if (s.physics == 5) {
            cout << i + 1 << ". " << s.prizv << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "����� �������� ����" << endl;
    }
    file.close();
}

// �������� ����� �������� � ������ �� � ����
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

// ϳ������� ������� ���� � ���� (��� ������������ �������)
int calc_n(int n) {
    int res = 0;
    while (n != 0) {
        n /= 10;
        res++;
    }
    return res;
}

// ��������� ������� ���������� ������� ����� ��������
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

// �������� ��������� ������� �� ��� ��������
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

    // ��������� ��������� �������
    cout << "=======================================================================";
    for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
        cout << "=";
    }
    cout << endl;

    cout << "|" << setw(maxDigits) << right << "�";
    cout << "|" << setw(width) << left << "�������" << "| ���� | ������������ | Գ���� | ���������� | ����������� | " << endl;

    cout << "-----------------------------------------------------------------------";
    for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
        cout << "-";
    }
    cout << endl;

    // ��������� ����� ��������
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
    cout << "������ ������� ��������: "; cin >> n;

    Student* arr = new Student[n]; // �������� ��������� ������ ��������

    char filename[100];
    cout << "������ ��'� �����: "; cin >> filename;

    fill_arr(arr, n, filename); // ���������� ������ �� ����� � ����

    printHeader(filename, n); 

    cout << fixed << setprecision(2);
    cout << "������� ��������-��������: " << calculateExcellentStudentsPercentage(filename, n) << "%" << endl << endl;
    printStudentsWithExcellentPhysics(filename, n); 

    delete[] arr; 
    return 0;
}
