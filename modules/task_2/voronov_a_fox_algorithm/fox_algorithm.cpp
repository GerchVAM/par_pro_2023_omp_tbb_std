// Copyright 2023 Voronov Alexander 

#include "../../../modules/task_2/voronov_a_fox_algorithm/fox_algorithm.h"
#include <math.h>
#include <omp.h>
#include <algorithm>
#include <limits>
#include <random>

void matrix_fill(double* a, const int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);
    for (int i = 0; i < size * size; i++)
        a[i] = dis(gen);
}

bool is_equal_matrix(const double* a, const double* b, const int size) {
    for (int i = 0; i < size * size; i++) {
        if (std::fabs(a[i] - b[i]) > 0.01) {
            return false;
        }
    }
    return true;
}

void matrix_mult_seq(const double* a, const double* b, const int size, double* res) {
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

void fox_algorithm_OMP(double *a, double *b, double *res, int n, int count_proc) {
    int q = std::sqrt(count_proc);
    #pragma omp parallel num_threads(q * q)
    {
        int counter;
        int procNum = omp_get_thread_num();
        int i_proc = procNum / q;
        int j_proc = procNum % q;
        double *a_temp;
        double *b_temp;
        double *res_tmp;
        for (counter = 0; counter < q; counter++) {
            a_temp = a + (n * i_proc + ((i_proc + counter) % q)) * (n / q);
            b_temp = b + (n * ((i_proc + counter) % q) + j_proc) * (n / q);
            res_tmp = res + (n * i_proc + j_proc) * (n / q);
            for (int i = 0; i < n / q; i++) {
                for (int j = 0; j < n / q; j++) {
                    for (int k = 0; k < n / q; k++) {
                        res_tmp[i * n + j] += a_temp[i * n + k] * b_temp[k * n + j];
                    }
                }
            }
        }
    }
}
