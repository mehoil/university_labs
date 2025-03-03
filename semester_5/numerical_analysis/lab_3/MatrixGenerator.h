#pragma once

#include <iostream>
#include <vector>
#include <random>

class MatrixGenerator {
    double size;
    std::vector<std::vector<double>> eigenVectorsData;
    std::vector<std::vector<double>> inverseEigenVectorsData;
    std::vector<double> eigenValuesData;

    std::vector<std::vector<double>> symmetricMatrix;
public:

    MatrixGenerator(
        const int size, const double min, const double max, double minLambda = 0, double maxLambda = 0
    ) :
        size(size),
        eigenVectorsData(size, std::vector<double>(size)),
        inverseEigenVectorsData(size, std::vector<double>(size)),
        eigenValuesData(size),
        symmetricMatrix(size, std::vector<double>(size))
    {
        minLambda = minLambda == 0 && minLambda != min ? min : minLambda;
        maxLambda = maxLambda == 0 && maxLambda != max ? max : maxLambda;
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<> dis(min, max);
        std::uniform_real_distribution<> lambdaDis(minLambda, maxLambda);

        for (int i = 0; i < size; ++i) {
            eigenValuesData[i] = lambdaDis(gen);
            for (int j = 0; j < size; ++j) {
                eigenVectorsData[i][j] = dis(gen);
            }
        }
        
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                symmetricMatrix[i][j] = eigenVectorsData[i][j] * eigenValuesData[j];
            }
        }

        inverseEigenVectorsData = inverseMatrix(eigenVectorsData);
        symmetricMatrix = multiply(symmetricMatrix, inverseEigenVectorsData, size);
    }

    std::vector<std::vector<double>> getSymmetricMatrix() {
        return symmetricMatrix;
    }
    std::vector<std::vector<double>> getEigenVectorsData() {
        return eigenVectorsData;
    }
    std::vector<std::vector<double>> getInverseEigenVectorsData() {
        return inverseEigenVectorsData;
    }
    std::vector<double> getEigenValuesData() {
        return eigenValuesData;
    }

private:
    static std::vector<std::vector<double>> multiply(
        const std::vector<std::vector<double>>& matrix1,
        const std::vector<std::vector<double>>& matrix2,
        const int &size
    ) {
        std::vector<std::vector<double>> result(size, std::vector<double>(size, 0.0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        return result;
    }


    static std::vector<std::vector<double>> inverseMatrix(const std::vector<std::vector<double>>& A) {
        const int n = A.size();

        //  метод Гаусса-Жордана
        //  [A | I] I - единичная матрица
        std::vector<std::vector<double>> augmentedMatrix(n, std::vector<double>(2 * n, 0.0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                augmentedMatrix[i][j] = A[i][j];
            }
            augmentedMatrix[i][i + n] = 1.0;
        }

        for (int i = 0; i < n; ++i) {
            const double pivot = augmentedMatrix[i][i];
            for (int j = 0; j < 2 * n; ++j) {
                augmentedMatrix[i][j] /= pivot;
            }
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    const double factor = augmentedMatrix[j][i];
                    for (int k = 0; k < 2 * n; ++k) {
                        augmentedMatrix[j][k] -= factor * augmentedMatrix[i][k];
                    }
                }
            }
        }
        std::vector<std::vector<double>> inverse(n, std::vector<double>(n, 0.0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                inverse[i][j] = augmentedMatrix[i][j + n];
            }
        }

        return inverse;
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
};
