#pragma once
#include <complex>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef std::complex<double> Complex;

class VectorComplex {
    Complex* v;
public:
    int size;

    explicit VectorComplex(const int size = 0) : size(size) {
        v = new Complex[size]{ Complex(0, 0)};
    }

    VectorComplex(const VectorComplex& other) : size(other.size) {
        v = new Complex[size];
        for (int i = 0; i < size; i++) {
            v[i] = other.v[i];
        }
    }

    VectorComplex(VectorComplex&& other) noexcept : v(other.v), size(other.size) {
        size = other.size;
        v = other.v;
        other.v = nullptr;
        other.size = 0;
    }

    ~VectorComplex() {
        delete[] v;
    }

    Complex& operator[](int i) const {
        i--;
        if (i < 0 || i >= size) {
            throw out_of_range("Invalid index");
        }
        return v[i];
    }

    VectorComplex operator+(const VectorComplex& other) const {
        if (other.size != size) {
            throw invalid_argument("Invalid vector size");
        }

        VectorComplex ans(size);
        for (int i = 0; i < size; i++) {
            ans.v[i] = v[i] + other.v[i];
        }
        return ans;
    }

    VectorComplex operator-(const VectorComplex& other) const {
        if (other.size != size) {
            throw invalid_argument("Invalid vector size");
        }

        VectorComplex ans(size);
        for (int i = 0; i < size; i++) {
            ans.v[i] = v[i] - other.v[i];
        }
        return ans;
    }

    double norma() const {
        double ans = 0;
        for (int i = 0; i < size; i++) {
            if (abs(v[i]) > ans) {
                ans = abs(v[i]);
            }
        }
        return ans;
    }

    void generate(const double A = 1, const double B = 100) const {
        for (int i = 0; i < size; i++) {
            v[i] = static_cast<double>(rand()) / RAND_MAX * (B - A) + A;
        }
    }

    void set_size(const int new_size) {
        delete[] v;
        size = new_size;
        v = new Complex[size];
    }

    VectorComplex& operator=(const VectorComplex& other) {
        if (this == &other) {
            return *this;
        }

        set_size(other.size);
        for (int i = 0; i < size; i++) {
            v[i] = other.v[i];
        }
        return *this;
    }

    VectorComplex& operator=(VectorComplex&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] v;
        v = other.v;
        size = other.size;
        other.v = nullptr;
        other.size = 0;
        return *this;
    }
};


inline void print(const VectorComplex &x) {
    for (int i = 1; i <= x.size; i++) {
        cout << x[i] << ' ';
    }
    cout << endl;
}


class VectorDouble {
    double* v;
public:
    int size;

    explicit VectorDouble(const int size = 0) : size(size) {
        v = new double[size]{ static_cast<double>(0) };
    }

    VectorDouble(const VectorDouble& other) : size(other.size) {
        v = new double[size];
        for (int i = 0; i < size; i++) {
            v[i] = other.v[i];
        }
    }

    VectorDouble(VectorDouble&& other) noexcept : v(other.v), size(other.size) {
        size = other.size;
        v = other.v;
        other.v = nullptr;
        other.size = 0;
    }

    ~VectorDouble() {
        delete[] v;
    }

    double& operator[](int i) const {
        i--;
        if (i < 0 || i >= size) {
            throw out_of_range("Invalid index");
        }
        return v[i];
    }

    VectorDouble operator+(const VectorDouble& other) const {
        if (other.size != size)
            throw invalid_argument("Invalid vector size");

        VectorDouble ans(size);
        for (int i = 0; i < size; i++) {
            ans.v[i] = v[i] + other.v[i];
        }
        return ans;
    }

    VectorDouble operator-(const VectorDouble& other) const {
        if (other.size != size) {
            throw invalid_argument("Invalid vector size");
        }

        VectorDouble ans(size);
        for (int i = 0; i < size; i++) {
            ans.v[i] = v[i] - other.v[i];
        }
        return ans;
    }

    double norma() const {
        double ans = 0;
        for (int i = 0; i < size; i++) {
            if (abs(v[i]) > ans) {
                ans = abs(v[i]);
            }
        }
        return ans;
    }

    void generate(const double A = 1, const double B = 100) const {
        for (int i = 0; i < size; i++) {
            v[i] = static_cast<double>(rand()) / RAND_MAX * (B - A) + A;
        }
    }

    void set_size(const int new_size) {
        delete[] v;
        size = new_size;
        v = new double[size];
    }

    VectorDouble& operator=(const VectorDouble& other) {
        if (this == &other) {
            return *this;
        }

        set_size(other.size);
        for (int i = 0; i < size; i++) {
            v[i] = other.v[i];
        }
        return *this;
    }

    VectorDouble& operator=(VectorDouble&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] v;
        v = other.v;
        size = other.size;
        other.v = nullptr;
        other.size = 0;
        return *this;
    }
};


inline void print(const VectorDouble &x) {
    for (int i = 1; i <= x.size; i++) {
        cout << x[i] << ' ';
    }
    cout << endl;
}