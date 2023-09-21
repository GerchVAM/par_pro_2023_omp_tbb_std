// Copyright 2023 Voronov Alexander

#ifndef MODULES_TASK_2_VORONOV_A_FOX_ALGORITHM_FOX_ALGORITHM_H_
#define MODULES_TASK_2_VORONOV_A_FOX_ALGORITHM_FOX_ALGORITHM_H_

void matrix_fill(double*, const int);
bool is_equal_matrix(const double*, const double*, const int);
void matrix_mult_seq(const double*, const double*, const int, double*);
void fox_algorithm_OMP(double*, double*, double*, int, int);


#endif  // MODULES_TASK_2_VORONOV_A_FOX_ALGORITHM_FOX_ALGORITHM_H_
