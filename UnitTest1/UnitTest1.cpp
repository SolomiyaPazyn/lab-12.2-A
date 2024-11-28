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

			// Створюємо тестовий масив студентів
			Student students[n] = {
				{"Ivanenko", 1, KN, 5, 4, 3},
				{"Petrenko", 2, AI, 5, 5, 5}
			};

			// Викликаємо функцію запису
			writeStudentsToFile(students, n, testFile);

			// Створюємо масив для зчитування
			Student readStudents[n];

			// Викликаємо функцію читання
			readStudentsFromFile(readStudents, n, testFile);

			// Перевіряємо відповідність записаних і прочитаних даних
			for (int i = 0; i < n; i++) {
				Assert::AreEqual(std::string(students[i].prizv), std::string(readStudents[i].prizv));
				Assert::AreEqual(students[i].course, readStudents[i].course);
				Assert::AreEqual((int)students[i].major, (int)readStudents[i].major);
				Assert::AreEqual(students[i].physics, readStudents[i].physics);
				Assert::AreEqual(students[i].math, readStudents[i].math);
				Assert::AreEqual(students[i].it, readStudents[i].it);
			}

			// Видаляємо тестовий файл
			remove(testFile);
		
		}
	};
}
