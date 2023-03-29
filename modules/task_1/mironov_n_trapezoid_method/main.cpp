// Copyright 2023 Mironov Nikita
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "./trapezoid.h"

double f1(std::vector<double> values) {
    double x = values[0];
    return x*x;
}

double f2(std::vector<double> values) {
    double x = values[0];
    double y = values[1];
    return x*y;
}

double f3(std::vector<double> values) {
    double x = values[0];
    double y = values[1];
    double z = values[2];
    return x*y*z;
}

double f4(std::vector<double> values) {
    double x = values[0];
    double y = values[1];
    double z = values[2];
    return sqrt((x*x) + y - z);
}

TEST(trapezoid, dimensions_mistake_test) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {3, 8};
    bounds[1] = {1, 4};
    bounds[2] = {1, 9};
    int dimensions = 2;

    EXPECT_ANY_THROW(trapezoid_method(f1, bounds, dimensions, 10));
}

TEST(trapezoid, 1d_test) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {3, 8};
    int dimensions = 1;
    double integration_result = 485/3;
    double method_result = trapezoid_method(f1, bounds, dimensions, 10);
    double tolerance = 0.1;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

TEST(trapezoid, 2d_test) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {3, 8};
    bounds[1] = {1, 4};
    int dimensions = 2;
    double integration_result = 825/4;
    double method_result = trapezoid_method(f2, bounds, dimensions, 10);
    double tolerance = 0.1;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

TEST(trapezoid, 3d_test_1) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {3, 8};
    bounds[1] = {1, 4};
    bounds[2] = {0, 9};
    int dimensions = 3;
    double integration_result = 66825/8;
    double method_result = trapezoid_method(f3, bounds, dimensions, 10);
    double tolerance = 0.1;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

TEST(trapezoid, 3d_test_2) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {3, 8};
    bounds[1] = {1, 4};
    bounds[2] = {0, 9};
    int dimensions = 3;
    double integration_result = 713.774;
    double method_result = trapezoid_method(f4, bounds, dimensions, 10);
    double tolerance = 0.1;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
