#pragma once
#include "BandMatrix.h"

struct BandMatrixT final : BandMatrix
{
    BandMatrixT(const int N, const int L) : BandMatrix(N, L) {}

    int index(const int i, const int j) override {
        const int k = j - i + L - 1;
        if (k < 0 || k >= 2 * L - 1) {
            return -1;
        }
        if (j >= i) {
            return (j - i) * N + (i - 1);
        }
        return -1;
    }
};