#pragma once
#include "UtilityFunctions.h"
#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
#include <stdexcept>

double generateRandomNumber(const double min, const double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
double roundError(double error) {
    int power = std::floor(std::log10(std::abs(error)));
    // round up to 3 according to the task
    const double roundedError = std::round(error / std::pow(10, power - 2)) * std::pow(10, power - 2);
    return roundedError;
}


void printArr(const std::vector<std::vector<double>>& matrix, const int rows, const int cols) {
    std::cout << std::endl << std::string(1, ' ') << std::string(cols*10+cols, '-') << std::endl;
    for (int i = 0; i < rows; ++i) {
        std::cout  << '|';
        for (int j = 0; j < cols; ++j) {
            std::cout << std::fixed << std::setprecision(5) << std::setw(10) << matrix.at(i).at(j) << " ";
        }
        std::cout  << '|' << std::endl;
    }
    std::cout << std::string(1, ' ') << std::string(cols * 10+cols, '-') << std::endl;
}

void printArr(const std::vector<double>& vector, const int size) {
    std::cout << std::endl << std::string(20, '-') << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << std::fixed << std::setprecision(5) << '|'
                  << std::setw(2) << "[" << i << "] = "
                  << std::setw(10) << std::setfill(' ') << vector.at(i)
                  << std::setw(2) << '|' << std::endl;
    }
    std::cout << std::endl << std::string(20, '-') << std::endl << std::endl;
}
