#pragma once
#include "Test.h"
#include "MatrixGenerator.h"
#include "InverseIterationsMethod.h"

#include <iostream>
#include <iomanip>

void testOne()
{
    constexpr int averageTests = 10;

    constexpr int sizes[] = { 10, 30, 50 };
    constexpr int lambdaRange[] = { 2, 50 };
    constexpr int eigenVectorsValuesERange[] = {-5, -8};

    std::cout << std::endl << std::string(150, '-') << std::endl;
    std::cout << std::setw(5) << "Test" 
              << std::setw(10) << "Size" 
              << std::setw(18) << "Lambda range" 
              << std::setw(10) << "E" 
              << std::setw(24) << "Average E val" 
              << std::setw(25) << "Average E vec" 
              << std::setw(25) << "Average measure r" 
              << std::setw(31) << "Average iterations number" 
              << std::endl;
    std::cout << std::string(150, '-') << std::endl;

    int N = sizes[0];
    int lambda = lambdaRange[0];

    int testNumber = 1;
    for (int counterSizes = 0; counterSizes < sizeof(sizes) / sizeof(sizes[0]); ++counterSizes) {
        N = sizes[counterSizes];
        for (int counterLambdaRange = 0; counterLambdaRange < sizeof(lambdaRange) / sizeof(lambdaRange[0]); ++counterLambdaRange) {
            lambda = lambdaRange[counterLambdaRange];
            for (int counterE = 0; counterE < sizeof(eigenVectorsValuesERange) / sizeof(eigenVectorsValuesERange[0]); ++counterE) {
                const int E = eigenVectorsValuesERange[counterE];
                double averageEVec = 0;
                double averageEVal = 0;
                double averageR = 0;
                int averageIterationsNumber = 0;
                for (size_t i = 0; i < averageTests; ++i) {
                    auto* generator = new MatrixGenerator(N, -100, 100, -lambda, lambda);
                    std::vector<std::vector<double>> symmetricMatrix = generator->getSymmetricMatrix();

                    auto* finder = new InverseIterationsMethod(N, symmetricMatrix, std::pow(10, E), std::pow(10, E), 1000);
                    finder->solve();
                    const double Evec = finder->getResultedEigenVectorsE();
                    const double Eval = finder->getResultedEigenValuesE();
                    const double r = finder->getR();
                    const int IterationsNumber = finder->getIterationsNumber();

                    averageEVec += Evec;
                    averageEVal += Eval;
                    averageR += r;
                    averageIterationsNumber += IterationsNumber;

                    if (i == averageTests-1) {
                        averageEVec /= averageTests;
                        averageEVal /= averageTests;
                        averageR /= averageTests;
                        averageIterationsNumber /= averageTests;

                        std::vector<double> firstEigenVector = finder->getEigenVectorByFirstMinEigenValue();
                        std::cout << std::setw(5) << testNumber
                                  << std::setw(10) << N 
                                  << std::setw(12) << -lambda<<':'<< lambda 
                                  << std::scientific << std::setprecision(1) << std::setw(17) << std::pow(10, E)
                                  << std::scientific << std::setprecision(3) << std::setw(20) << averageEVal
                                  << std::scientific << std::setprecision(3) << std::setw(25) << averageEVec
                                  << std::scientific << std::setprecision(3) << std::setw(25) << averageR
                                  << std::setw(23) << averageIterationsNumber
                                  << std::endl;
                        ++testNumber;
                    }
                }
            }
        }
    }

    
}
