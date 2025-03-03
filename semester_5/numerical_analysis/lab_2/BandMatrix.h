#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Vector.h"

using namespace std;

inline int k0(const int i, const int L) {
    return max(1, i - L + 1);
}

inline int kN(const int i, const int N, const int L) {
    return min(N, i + L - 1);
}

struct BandMatrixComplex final {
    ~BandMatrixComplex() = default;

    int N;
    int L;
    vector<Complex> diags;

    BandMatrixComplex(const int n, const int l) : N(n), L(l), diags(L* N, Complex(0.0, 0.0)) {}
    void BandMatrixRavn(const BandMatrixComplex& A) {
        diags = A.diags;
    }

    int index(const int i, const int j) const {
        const int k = j - i + L - 1;
        if (k < 0 || k >= 2 * L - 1) {
            return -1;
        }
        if (j >= i) {
            return (j - i) * N + (i - 1);
        }
        return (i - j) * N + (j - 1);
    }

    Complex& operator()(const int i, const int j) {
        const int idx = index(i, j);
        if (idx == -1) {
            return zero;
        }
        return diags[idx];
    }

    Complex zero = Complex(0.0, 0.0);

    // ��������� ������� �� ������
    VectorComplex operator*(const VectorComplex& vec) {
        if (vec.size != N) {
            throw invalid_argument("Wrong size");
        }

        VectorComplex result(N);

        for (int i = 1; i <= N; ++i) {
            for (int j = k0(i, L); j <= kN(i, N, L); j++) {
                result[i] += (*this)(i, j) * vec[j];
            }
        }
        return result;
    }

    void generate(const double A, const double B) {
        for (int i = 1; i <= N; i++) {
            for (int j = i; j <= kN(i, N, L); j++) {
                (*this)(i, j) = Complex(static_cast<double>(rand()) / RAND_MAX * (B - A) + A, 0);
            }
        }
    }

    void makeConditioned(const bool wellConditioned, const int k) {
        const int coff = pow(10, k);
        if (wellConditioned) {
            for (int i = 1; i <= N; i++) {
                (*this)(i, i) *= Complex(coff, 0);
            }
        }
        else {
            for (int i = 1; i <= N; i++) {
                (*this)(i, i) /= Complex(coff, 0);
            }
        }
    }
};

struct BandMatrix {
    virtual ~BandMatrix() = default;

    int N;
    int L;
    vector<double> diags;

    BandMatrix(const int n, const int l) : N(n), L(l), diags(L* N, 0.0) {}
    void BandMatrixRavn(const BandMatrix& A) {
        diags = A.diags;
    }

    virtual int index(const int i, const int j) {
        const int k = j - i + L - 1;
        if (k < 0 || k >= 2 * L - 1) {
            return -1;
        }
        if (j >= i) {
            return (j - i) * N + (i - 1);
        }
        return (i - j) * N + (j - 1);
    }

    virtual double& operator()(const int i, const int j) {
        const int idx = index(i, j);
        if (idx == -1) {
            return zero;
        }
        return diags[idx];
    }

    double zero = 0.0;

    // ��������� ������� �� ������
    VectorDouble operator*(const VectorDouble& vec) {
        if (vec.size != N) {
            throw invalid_argument("Wrong size");
        }

        VectorDouble result(N);

        for (int i = 1; i <= N; ++i) {
            for (int j = k0(i, L); j <= kN(i, N, L); j++) {
                result[i] += (*this)(i, j) * vec[j];
            }
        }
        return result;
    }

    void generate(const double A, const double B) {
        for (int i = 1; i <= N; i++) {
            for (int j = i; j <= kN(i, N, L); j++) {
                (*this)(i, j) = static_cast<double>(rand()) / RAND_MAX * (B - A) + A;
            }
        }
    }

    void make_conditioned(const bool wellConditioned, const int k) {
        const int coef = pow(10, k);
        if (wellConditioned) {
            for (int i = 1; i <= N; i++) {
                (*this)(i, i) *= static_cast<double>(coef);
            }
        }
        else {
            for (int i = 1; i <= N; i++) {
                (*this)(i, i) /= static_cast<double>(coef);
            }
        }
    }
};

inline void print(BandMatrix& A) {
    const int n = A.N;
    int l = A.L;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (std::abs(i - j) < l) {
                std::cout << std::setw(10) << left << A(i, j) << " ";
            }
            else {
                std::cout << std::setw(10) << 0.0 << " ";
            }
        }
        std::cout << std::endl;
    }
    cout << endl;
}

inline void printT(BandMatrix& A) {
    const int n = A.N;
    int l = A.L;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (std::abs(i - j) < l && i<=j) {
                std::cout << std::setw(10) << left << A(i, j) << " ";
            }
            else {
                std::cout << std::setw(10) << 0.0 << " ";
            }
        }
        std::cout << std::endl;
    }
    cout << endl;
}

inline void printTransposed(BandMatrix& A) {
    const int n = A.N;
    int l = A.L;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (std::abs(i - j) < l && i >= j) {
                std::cout << std::setw(10) << left << A(i, j) << " ";
            }
            else {
                std::cout << std::setw(10) << 0.0 << " ";
            }
        }
        std::cout << std::endl;
    }
    cout << endl;
}

inline BandMatrix multiply(BandMatrix &A, BandMatrix &B)
{
    const size_t n = A.N;
    BandMatrix result(n, A.L);

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = k0(i, A.L); j <= kN(i, A.N, A.L); ++j) {
            for (size_t k = 1; k <= n; ++k) {
                if (i >= j) {     //����� �� ����� ������ ������� ���� � ���� ����� ����� ������� ����������,
                                  //� � 1 2 � 2 1 ����� ������ �� ���� ������ � �������
                    result(i, j) += A(i, k) * B(k, j);
                }
            }
        }
    }

    return result;
}