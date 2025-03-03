#ifndef AVGERRORUTIL_H
#define AVGERRORUTIL_H
#include "BandMatrix.h"
#include "BandMatrixT.h"
#include "TransposedBandMatrixT.h"


inline VectorDouble choleskyDecomposition(BandMatrix& A, const VectorDouble& f, const bool doPrint = false) {
	BandMatrix copyM = A;
	const int N = A.N;
	const int L = A.L;

	for (int i = 1; i <= N; ++i) {
		double S = A(i, i);
		for (int k = k0(i, L); k < i; ++k) {
			S -= copyM(k, i) * copyM(k, i);
		}

		if (S < 0) {
			throw invalid_argument("The square is negative");
		}
		copyM(i, i) = sqrt(S);

		for (int j = i + 1; j <= kN(i, N, L); ++j) {
			S = A(i, j);
			for (int k = k0(i, L); k < i; ++k) {
				S -= copyM(k, i) * copyM(k, j);
			}

			copyM(i, j) = S / copyM(i, i);
		}
	}
	if (doPrint) {
		cout << "\nМатрица Т:\n";
		printT(copyM);


		cout << "\nМатрица Т транспонированная:\n";
		printTransposed(copyM);

		BandMatrixT T(copyM.N, copyM.L);
		T.BandMatrixRavn(copyM);
		TransposedBandMatrixT transposedT(copyM.N, copyM.L);
		transposedT.BandMatrixRavn(copyM);

		BandMatrix expectedA = multiply(transposedT, T);
		cout << "\nМатрица (T транспонированная)*T:\n";
		print(expectedA);
	}

	const VectorDouble y(N);
	VectorDouble x(N);
	// (T^T * y = f)
	for (int i = 1; i <= N; ++i) {
		double S = f[i];
		for (int j = k0(i, L); j <= (i - 1); ++j) {
			S -= copyM(j, i) * y[j];
		}
		y[i] = S / copyM(i, i);
	}

	// (T * x = y)
	for (int i = N; i >= 1; --i) {
		double S = y[i];
		for (int j = i + 1; j <= kN(i, N, L); ++j) {
			S -= copyM(i, j) * x[j];
		}
		x[i] = S / copyM(i, i);
	}

	return x;
}

inline VectorComplex choleskyComplexDecomposition(BandMatrixComplex& A, const VectorComplex& f) {
	BandMatrixComplex copyM = A;
	const int N = A.N;
	const int L = A.L;

	for (int i = 1; i <= N; ++i) {
		Complex S = A(i, i);
		for (int k = k0(i, L); k < i; ++k) {
			S -= copyM(k, i) * copyM(k, i);
		}

		copyM(i, i) = sqrt(S);

		for (int j = i + 1; j <= kN(i, N, L); ++j) {
			S = A(i, j);
			for (int k = k0(i, L); k < i; ++k) {
				S -= copyM(k, i) * copyM(k, j);
			}

			copyM(i, j) = S / copyM(i, i);
		}
	}

	const VectorComplex y(N);
	VectorComplex x(N);
	// (T^T * y = f)
	for (int i = 1; i <= N; ++i) {
		Complex S = f[i];
		for (int j = k0(i, L); j <= (i - 1); ++j) {
			S -= copyM(j, i) * y[j];
		}
		y[i] = S / copyM(i, i);
	}

	// (T * x = y)
	for (int i = N; i >= 1; --i) {
		Complex S = y[i];
		for (int j = i + 1; j <= kN(i, N, L); ++j) {
			S -= copyM(i, j) * x[j];
		}
		x[i] = S / copyM(i, i);
	}

	return x;
}

inline long double getAvgError1(const int N, const int L, const double A, const double B) {
    long double averageError{};
    BandMatrixComplex matrix(N, L);
    const VectorComplex exactX(N);
    for (int j = 1; j <= 10; j++) {
        matrix.generate(A, B);
        exactX.generate(A, B);
        VectorComplex f = matrix * exactX;
        VectorComplex x = choleskyComplexDecomposition(matrix, f);
        VectorComplex error = exactX - x;
        averageError += error.norma();
    }
    averageError /= 10;
    return averageError;
}

inline long double getAvgError2(const int N, const int L, const double A, const double B, const bool wellConditioned, const int k = 3) {
    long double averageError{};
    BandMatrixComplex matrix(N, L);
    const VectorComplex exactX(N);
    for (int j = 1; j <= 10; j++) {
        matrix.generate(A, B);
        matrix.makeConditioned(wellConditioned, k);
        exactX.generate(A, B);
        VectorComplex f = matrix * exactX;
        VectorComplex x = choleskyComplexDecomposition(matrix, f);
        VectorComplex error = exactX - x;
        averageError += error.norma();
    }
    averageError /= 10;
    return averageError;
}

#endif //AVGERRORUTIL_H
