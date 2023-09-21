// Copyright 2023 Voronov Alexander

#include "../../../modules/task_1/voronov_a_fox_algorithm/fox_algorithm.h"
#include <math.h>
#include <algorithm>
#include <limits>
#include <random>

void matrix_fill(double* a, const int size) {
    std::random_device rand_d;
    std::mt19937 gen(rand_d());
    std::uniform_real_distribution<> rnd_num(0.0, 1000.0);
    for (int i = 0; i < size * size; i++)
        a[i] = rnd_num(gen);
}

bool is_equal_matrix(const double* a, const double* b, const int size) {
    for (int i = 0; i < size * size; i++) {
        if (std::fabs(a[i] - b[i]) > 0.01) {
            return false;
        }
    }
    return true;
}

void matrix_mult_seq(const double* a, const double* b,
                     const int size, double* res) {
    double temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp = 0;
            for (int k = 0; k < size; k++) {
                temp += a[i * size + k] * b[k * size + j];
            }
            res[i * size + j] = temp;
        }
    }
}


void block_mtrx_mult(const double* a, const double* b,
                     const int size, double* block_count) {
    int b_size = std::sqrt(size);
    for (int i = 0; i < size * size; i++)
        block_count[i] = 0;
    double temp;
    for (int i = 0; i < size; i += b_size) {
        for (int j = 0; j < size; j += b_size) {
            for (int k = 0; k < size; k += b_size) {
                for (int ii = i; ii < std::min(size, i + b_size); ii++) {
                    for (int jj = j; jj < std::min(size, j + b_size); jj++) {
                        temp = 0;
                        for (int kk = k; kk < std::min(size, k + b_size);
                        kk++) {
                            temp += a[ii * size + kk] * b[kk * size + jj];
                        }
                        block_count[ii * size + jj] += temp;
                    }
                }
            }
        }
    }
}
