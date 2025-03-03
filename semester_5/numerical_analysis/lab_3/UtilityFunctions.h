#pragma once

#ifndef TOOLSFUNC_H
#define TOOLSFUNC_H

#include <vector>

double generateRandomNumber(double min, double max);

double roundError(double error);

void printArr(const std::vector<std::vector<double>>& matrix, int rows, int cols);

void printArr(const std::vector<double>& vector, int size);

#endif
