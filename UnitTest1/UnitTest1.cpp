#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 12.2 A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const char* testFile = "test_students.bin";
			const int n = 2;

			// ��������� �������� ����� ��������
			Student students[n] = {
				{"Ivanenko", 1, KN, 5, 4, 3},
				{"Petrenko", 2, AI, 5, 5, 5}
			};

			// ��������� ������� ������
			writeStudentsToFile(students, n, testFile);

			// ��������� ����� ��� ����������
			Student readStudents[n];

			// ��������� ������� �������
			readStudentsFromFile(readStudents, n, testFile);

			// ���������� ���������� ��������� � ���������� �����
			for (int i = 0; i < n; i++) {
				Assert::AreEqual(std::string(students[i].prizv), std::string(readStudents[i].prizv));
				Assert::AreEqual(students[i].course, readStudents[i].course);
				Assert::AreEqual((int)students[i].major, (int)readStudents[i].major);
				Assert::AreEqual(students[i].physics, readStudents[i].physics);
				Assert::AreEqual(students[i].math, readStudents[i].math);
				Assert::AreEqual(students[i].it, readStudents[i].it);
			}

			// ��������� �������� ����
			remove(testFile);
		
		}
	};
}
