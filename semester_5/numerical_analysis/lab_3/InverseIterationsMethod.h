#pragma once

#include "TapeMatrix.h"

#include <vector>
#include <random>

#include "UtilityFunctions.h"

class InverseIterationsMethod{
    int size;
    std::vector<std::vector<double>> symmetricMatrix;
    double givenEigenVectorsE;
    double givenEigenValuesE;
    int maxIterationsNumber;

    double firstMinEigenValue;
    std::vector<double> eigenVectorByFirstMinEigenValue;
    int iterationsNumber;
    double resultedEigenVectorsE = 0;
    double resultedEigenValuesE = 0;
    double r = 10;
public:

    InverseIterationsMethod(
        const int size,
        const std::vector<std::vector<double>> &symmetricMatrix,
        const double eigenVectorsE,
        const double eigenValuesE,
        const int maxIterationsNumber
    ): size(size),
       symmetricMatrix(size, std::vector<double>(size)),
       givenEigenVectorsE(eigenVectorsE),
       givenEigenValuesE(eigenValuesE),
       maxIterationsNumber(maxIterationsNumber),
       firstMinEigenValue(0),
       eigenVectorByFirstMinEigenValue(size),
       iterationsNumber(0)
    {
       this->symmetricMatrix = symmetricMatrix;
    }

    void solve()
    {
        std::vector<double> x_rand(size);
        for (size_t i = 0; i < size; i++) {
            x_rand[i] = generateRandomNumber(-10, 10);
        }
        int k = 0;
        double q = 10;
        double maxVecE = 10;
        auto* system = new TapeMatrix(symmetricMatrix, size, size);
        while ((resultedEigenValuesE > givenEigenValuesE || maxVecE > givenEigenVectorsE) && k <  maxIterationsNumber)
        {
            std::vector<double> v = normalizeVector(x_rand);

            system->solveSLAE(v);
            if (system->isSolved()) {
                x_rand = system->getSolution();
                double qPrev = q;
                q = 0;
                for (int i = 0; i < size; ++i) {
                    q += v[i] * x_rand[i];
                }
                firstMinEigenValue = 1 / q;
                maxVecE = -10;
                for (size_t i = 0; i < size && !eigenVectorByFirstMinEigenValue.empty(); i++) {
                    double tmp = std::abs(std::abs(v[i]) - std::abs(eigenVectorByFirstMinEigenValue[i]));
                    if (maxVecE < tmp) {
                        maxVecE = tmp;
                    }
                }
                resultedEigenVectorsE = maxVecE;
                resultedEigenValuesE = std::abs(std::abs(q) - std::abs(qPrev));
                eigenVectorByFirstMinEigenValue = v;
            }
            ++k;
        }
        iterationsNumber = k;
        std::vector<double> _r(size);
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                _r[i] += symmetricMatrix[i][j] * eigenVectorByFirstMinEigenValue[j];
            }
            _r[i] -= eigenVectorByFirstMinEigenValue[i] * firstMinEigenValue;
            if (_r[i]<r) {
                r = _r[i];
            }
        }
    }

    static std::vector<double> normalizeVector(const std::vector<double>& vector) {
        double sum = 0.0;
        for (const double element : vector) {
            sum += element * element;
        }

        const double magnitude = std::sqrt(sum);
        std::vector<double> normalizedVector;
        for (const double element : vector) {
            normalizedVector.push_back(element / magnitude);
        }

        return normalizedVector;
    }

    std::vector<double> getEigenVectorByFirstMinEigenValue() {
        return eigenVectorByFirstMinEigenValue;
    }
    double getFirstMinEigenValue() const {
        return firstMinEigenValue;
    }
    double getIterationsNumber() const {
        return iterationsNumber;
    }
    double getR() const {
        return r;
    }
    double getResultedEigenVectorsE() const {
        return resultedEigenVectorsE;
    }
    double getResultedEigenValuesE() const {
        return resultedEigenValuesE;
    }
};
