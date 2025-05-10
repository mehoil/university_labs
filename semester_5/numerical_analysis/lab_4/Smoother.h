#ifndef SMOOTHER_H
#define SMOOTHER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Smoother {
    std::vector<double> X, Y, YY;
    int N;
    int IER;

public:
    Smoother() : N(0), IER(0) {}

    void readData(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename;
            return;
        }

        X.clear();
        Y.clear();
        double x, y;
        file >> N;
        for (int i = 0; i < N; i++) {
            file >> x >> y;
            X.push_back(x);
            Y.push_back(y);
        }
        file.close();
    }

    void smooth() {
        IER = 0;
        YY.resize(N);

        // Проверка порядка
        for (int i = 1; i < N; ++i) {
            if (X[i] <= X[i - 1]) {
                IER = 2;
                return;
            }
        }

        YY[0] = Y[0];
        YY[N - 1] = Y[N - 1];

        for (int i = 1; i < N - 1; ++i) {
            const double x0 = X[i - 1];
            const double x1 = X[i];
            const double x2 = X[i + 1];

            const double y0 = Y[i - 1];
            const double y1 = Y[i];
            const double y2 = Y[i + 1];

            const double h0 = x1 - x0;
            const double h1 = x2 - x1;

            const double num = y0 * h1 * (h0 + h1) + y1 * (h0 * h0 + h1 * h1) + y2 * h0 * (h0 + h1);
            const double denom = 2 * (h0 * h0 + h0 * h1 + h1 * h1);

            YY[i] = num / denom;
        }

        bool allEqual = true;
        for (int i = 0; i < N; ++i) {
            if (abs(YY[i] - Y[i]) > 1e-12) {
                allEqual = false;
                break;
            }
        }

        if (allEqual)
            IER = 1;
    }

    void print() {
        std::cout << "X = [ ";
        for (const double x : X) {
            std::cout << x << " ";
        }
        std::cout << "]" << std::endl;

        std::cout << "Y = [ ";
        for (const double y : Y) {
            std::cout << y << " ";
        }
        std::cout << "]" << std::endl;

        std::cout << "\nIER = " << IER << std::endl;

        if (IER != 2) {
            std::cout << "YY = [ ";
            for (const double yy : YY) {
                std::cout << yy << " ";
            }
            std::cout << "]" << std::endl;
        }
    }
};

#endif //SMOOTHER_H
