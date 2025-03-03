#include <iostream>
#include <cmath>
#include <iomanip>
#include "AvgErrorUtil.h"
#include "Vector.h"
#include "BandMatrix.h"

using namespace std;

void test1() {
	constexpr int n = 4;
	constexpr int l = 2;

	BandMatrix matrix(n, l);
	matrix(1, 1) = 4; matrix(1, 2) = 2;
	matrix(2, 1) = 2; matrix(2, 2) = 17; matrix(2, 3) = -5;
	matrix(3, 2) = -5; matrix(3, 3) = 11;  matrix(3, 4) = 1;
	matrix(4, 3) = 1; matrix(4, 4) = 6;

	const VectorDouble f(n);
	f[1] = 4; f[2] = 2; f[3] = 1; f[4] = 6;


	cout << "Исходная матрица: \n";
	print(matrix);
	cout << "Вектор F:\n";
	print(f);

	const VectorDouble x = choleskyDecomposition(matrix, f, true);

	cout << "\nВектор X: ";
	print(x);

	cout << "\nРезультат произведения матрицы и полученного вектора Х:\n";
	const VectorDouble newF = matrix * x;
	print(newF);
}

void test2() {
	constexpr int n = 4;
	constexpr int l = 2;

	BandMatrix matrix(n, l);
	matrix(1, 1) = -4; matrix(1, 2) = 2;      // -4 гарантирует отрицательный корень
	matrix(2, 1) = 2; matrix(2, 2) = 17; matrix(2, 3) = -5;
	matrix(3, 2) = -5; matrix(3, 3) = 11;  matrix(3, 4) = 1;
	matrix(4, 3) = 1; matrix(4, 4) = 6;

	const VectorDouble f(n);
	f[1] = 4; f[2] = 2; f[3] = 1; f[4] = 6;

	cout << "Исходная матрица: \n";
	print(matrix);
	cout << "Вектор F:\n";
	print(f);

	const VectorDouble x = choleskyDecomposition(matrix, f, true);

	cout << "\nВектор X: ";
	print(x);

	cout << "\nРезультат произведения матрицы и полученного вектора Х:\n";
	const VectorDouble newF = matrix * x;
	print(newF);
}

void table1() {
	cout << setw(15) << left << "Размерность"
		<< setw(25) << "Отношение L/N"
		<< setw(20) << "Средняя погрешность"
		<< endl;
	std::cout << std::string(60, '-') << std::endl;

	constexpr double A = -10;
	for (int i = 8; i <= 1024; i *= 2) {
		constexpr double B = 10;
		const int N = i;

		int L = ceil(N / 10.0);
		long double average_error = getAvgError1(i, L, A, B);
		cout << std::setw(15) << left << i
			<< std::setw(25) << "1/10"
			<< std::setw(20) << left << std::setprecision(6) << average_error
			<< std::endl;


		L = ceil(N / 4.0);
		average_error = getAvgError1(i, L, A, B);
		cout << std::setw(15) << left << i
			<< std::setw(25) << "1/4"
			<< std::setw(20) << left << std::setprecision(6) << average_error
			<< std::endl;
	}
}

void table2() {
	cout << setw(15) << left << "Размерность"
		<< setw(25) << "Отношение L/N"
		<< setw(20) << "Средняя погрешность"
		<< endl;
	std::cout << std::string(60, '-') << std::endl;

	constexpr double A = -10;
	for (int i = 8; i <= 1024; i *= 2) {
		constexpr double B = 10;
		const int N = i;

		int L = ceil(N / 10.0);
		long double averageError = getAvgError2(i, L, A, B, true);
		cout << std::setw(15) << left << i
			<< std::setw(25) << "1/10"
			<< std::setw(20) << left << std::setprecision(6) << averageError
			<< std::endl;


		L = ceil(N / 4.0);
		averageError = getAvgError2(i, L, A, B, true);
		cout << std::setw(15) << left << i
			<< std::setw(25) << "1/4"
			<< std::setw(20) << left << std::setprecision(6) << averageError
			<< std::endl;
	}
}

void table3() {
	cout << setw(15) << left << "Размерность"
		<< setw(25) << "k"
		<< setw(20) << "Средняя погрешность"
		<< endl;
	std::cout << std::string(60, '-') << std::endl;

	constexpr double A = -10;
	for (int i = 8; i <= 1024; i *= 2) {
		constexpr double B = 10;
		const int N = i;

		const int L = ceil(N / 10.0);
		int k = 2;
		long double averageError = getAvgError2(i, L, A, B, false, k);
		cout << std::setw(15) << left << i
			<< std::setw(25) << k
			<< std::setw(20) << left << std::setprecision(6) << averageError
			<< std::endl;
		k = 4;
		averageError = getAvgError2(i, L, A, B, false, k);
		cout << std::setw(15) << left << i
			<< std::setw(25) << k
			<< std::setw(20) << left << std::setprecision(6) << averageError
			<< std::endl;
		k = 6;
		averageError = getAvgError2(i, L, A, B, false, k);
		cout << std::setw(15) << left << i
			<< std::setw(25) << k
			<< std::setw(20) << left << std::setprecision(6) << averageError
			<< std::endl;
	}
}


void menu() {
	int x = 1;
	while (x) {
		cout << "1.  Тестовый пример\n";
		cout << "2.  Таблица погрешностей\n";
		cout << "3.  Таблица погрешностей для хорошо обусловленной матрицы\n";
		cout << "4.  Таблица погрешностей для плохо обусловленной матрицы\n";
		cout << "5.  Тестовый пример с отрицательно определенной матрицей\n";
		cout << "0.  Выход\n\n";
		cin >> x;
		switch (x) {
			case 1: {
				test1();
				cout << endl << endl;
				break;
			}
			case 2: {
				cout << defaultfloat;
				table1();

				break;
			}
			case 3: {
				cout << defaultfloat;
				cout << "Для хорошо обусловленной матрицы\n";
				table2();

				break;
			}
			case 4: {
				cout << defaultfloat;
				cout << "Для плохо обусловленной матрицы\n";
				table3();

				break;
			}
			case 5: {
				test2();
				cout << endl << endl;
				break;
			}
			default: {
				break;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	menu();
	return 0;
}


