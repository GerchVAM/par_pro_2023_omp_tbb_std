// Copyright 2023 Voronov Alexander 

#include <gtest/gtest.h>
#include <omp.h>
#include "../../../modules/task_2/voronov_a_fox_algorithm/fox_algorithm.h"

#define SIZE_SMALL 3
#define SIZE_MEDIUM 10
#define SIZE_LARGE 50

TEST(Fox_Algorithm, Is_Equal_Matrixes_Correct) {
    double a[SIZE_SMALL * SIZE_SMALL];
    bool res;
    matrix_fill(a, SIZE_SMALL);
    res = is_equal_matrix(a, a, SIZE_SMALL);

    ASSERT_EQ(res, true);
}

TEST(Fox_Algorithm, Is_Unequal_Matrix_Correct) {
    double a[SIZE_SMALL * SIZE_SMALL] = {   1, 1, 1,
                                            1, 1, 1,
                                            1, 1, 1 };
    double b[SIZE_SMALL * SIZE_SMALL] = {   2, 2, 2,
                                            2, 2, 2,
                                            2, 2, 2 };
    bool res;
    matrix_fill(a, 3);
    res = is_equal_matrix(a, b, SIZE_SMALL);

    ASSERT_EQ(res, false);
}

TEST(Fox_Algorithm, Is_Matrix_Mult_Simple_Correct) {
    double a[SIZE_SMALL * SIZE_SMALL] = {   1, 1.5, 1,
                                            1, 1.5, 1,
                                            1, 1.5, 1 };
    double b[SIZE_SMALL * SIZE_SMALL] = {   2, 2, 2,
                                            2, 2, 2,
                                            2, 2, 2 };
    double res[SIZE_SMALL * SIZE_SMALL]{};
    double correct_res[SIZE_SMALL * SIZE_SMALL] = { 7, 7, 7,
                                                    7, 7, 7,
                                                    7, 7, 7 };
    bool result;
    matrix_mult_seq(a, b, SIZE_SMALL, res);
    result = is_equal_matrix(res, correct_res, SIZE_SMALL);
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, OMP_Matrix_Mult_Correct_Small) {
    const int count_of_proc = 3;
    double a[SIZE_SMALL * SIZE_SMALL] = {   9, 8, 7,
                                            6, 5, 4,
                                            3, 2, 1 };
    double b[SIZE_SMALL * SIZE_SMALL] = {   1, 2, 3,
                                            4, 5, 6,
                                            7, 8, 9 };
    double res[SIZE_SMALL * SIZE_SMALL]{};
    double true_res[SIZE_SMALL * SIZE_SMALL] = {    90,   114, 138,
                                                    54,   69,  84,
                                                    18,   24,  30 };
    bool result;
    fox_algorithm_OMP(a, b, res, SIZE_SMALL, count_of_proc);
    result = is_equal_matrix(res, true_res, SIZE_SMALL);

    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Any_Matrix_Mult_Equal_Result_Medium) {
    const int count_of_proc = 4;
    double* a = new double[SIZE_MEDIUM * SIZE_MEDIUM];
    double* b = new double[SIZE_MEDIUM * SIZE_MEDIUM];
    double* seq_res = new double[SIZE_MEDIUM * SIZE_MEDIUM]{};
    double* omp_res = new double[SIZE_MEDIUM * SIZE_MEDIUM]{};
    bool result;

    matrix_fill(a, SIZE_MEDIUM);
    matrix_fill(b, SIZE_MEDIUM);
    matrix_mult_seq(a, b, SIZE_MEDIUM, seq_res);
    fox_algorithm_OMP(a, b, omp_res, SIZE_MEDIUM, count_of_proc);
    result = is_equal_matrix(seq_res, omp_res, SIZE_MEDIUM);

    ASSERT_EQ(result, true);
    delete[] a;
    delete[] b;
    delete[] seq_res;
    delete[] omp_res;
}

TEST(Fox_Algorithm, Any_Matrix_Mult_Equal_Result_Large) {
    const int num_proc = 4;
    double* a = new double[SIZE_LARGE * SIZE_LARGE];
    double* b = new double[SIZE_LARGE * SIZE_LARGE];
    double* def_res = new double[SIZE_LARGE * SIZE_LARGE]{};
    double* fox_res = new double[SIZE_LARGE * SIZE_LARGE]{};
    bool result;

    matrix_fill(a, SIZE_LARGE);
    matrix_fill(b, SIZE_LARGE);
    matrix_mult_seq(a, b, SIZE_LARGE, def_res);
    fox_algorithm_OMP(a, b, fox_res, SIZE_LARGE, num_proc);

    result = is_equal_matrix(def_res, fox_res, SIZE_LARGE);

    ASSERT_EQ(result, true);
    delete[] a;
    delete[] b;
    delete[] def_res;
    delete[] fox_res;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
