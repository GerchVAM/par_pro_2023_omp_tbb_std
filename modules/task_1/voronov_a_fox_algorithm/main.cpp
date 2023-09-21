// Copyright 2023 Voronov Alexander

#include <gtest/gtest.h>
#include "../../../modules/task_1/voronov_a_fox_algorithm/fox_algorithm.h"

#define SIZE_SMALL 3

TEST(Fox_Algorithm, Is_Equal_Matrixes_Correct) {
    double a[SIZE_SMALL * SIZE_SMALL];
    bool result;
    matrix_fill(a, SIZE_SMALL);
    result = is_equal_matrix(a, a, SIZE_SMALL);
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Is_Unequal_Matrix_Correct) {
    double a[SIZE_SMALL * SIZE_SMALL] =  {  1, 1, 1,
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
    double true_res[SIZE_SMALL * SIZE_SMALL] = { 7, 7, 7,
                                                 7, 7, 7,
                                                 7, 7, 7 };
    bool result;
    matrix_mult_seq(a, b, SIZE_SMALL, res);
    result = is_equal_matrix(res, true_res, SIZE_SMALL);
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Is_Block_Matrix_Mult_Correct) {
    double a[SIZE_SMALL * SIZE_SMALL] = {   1, 1.5, 1,
                                            1, 1.5, 1,
                                            1, 1.5, 1 };
    double b[SIZE_SMALL * SIZE_SMALL] = {   2, 2, 2,
                                            2, 2, 2,
                                            2, 2, 2 };
    double res[SIZE_SMALL * SIZE_SMALL]{};
    double true_res[SIZE_SMALL * SIZE_SMALL] = { 7, 7, 7,
                                                 7, 7, 7,
                                                 7, 7, 7 };
    bool result;
    block_mtrx_mult(a, b, SIZE_SMALL, res);
    result = is_equal_matrix(res, true_res, SIZE_SMALL);

    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Any_Matrix_Multiplication_Equal_Result) {
    double a[SIZE_SMALL * SIZE_SMALL];
    double b[SIZE_SMALL * SIZE_SMALL];
    double def_res[SIZE_SMALL * SIZE_SMALL]{};
    double block_res[SIZE_SMALL * SIZE_SMALL]{};
    bool result;

    matrix_fill(a, SIZE_SMALL);
    matrix_fill(b, SIZE_SMALL);
    matrix_mult_seq(a, b, SIZE_SMALL, def_res);
    block_mtrx_mult(a, b, SIZE_SMALL, block_res);
    result = is_equal_matrix(def_res, block_res, SIZE_SMALL);

    ASSERT_EQ(result, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
