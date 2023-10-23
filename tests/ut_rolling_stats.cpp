//
// Created by Davide Pilastro on 10/21/23.
//


#include <gtest/gtest.h>
#include <random>
#include "rolling_stats.h"

TEST(TestRollingAverage, Test1Value){
    auto ra = RollingAverage<double>(5);
    ra.push_back(3.0);
    ASSERT_DOUBLE_EQ(3.0, ra.mean());
}

TEST(TestRollingAverage, Test2Values){
    auto ra = RollingAverage<double>(5);
    ra.push_back(3.0);
    ra.push_back(5.0);
    ASSERT_DOUBLE_EQ(4.0, ra.mean());
}

TEST(TestRollingAverage, TestRolling){
    auto ra = RollingAverage<double>(3);
    ra.push_back(3.0);
    ra.push_back(5.0);
    ra.push_back(2.0);
    ra.push_back(3.0);
    ra.push_back(5.0);
    ra.push_back(1.0);
    ASSERT_DOUBLE_EQ(3.0, ra.mean());
}

class TestParametricRollingAverage :public ::testing::TestWithParam<size_t> {
protected:
    RollingAverage<double> rolling_average_;

    TestParametricRollingAverage():
            rolling_average_(GetParam()){}
};

TEST_P(TestParametricRollingAverage, TestMean) {
    double lower_bound = 0;
    double upper_bound = 100;

    std::uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    std::default_random_engine re;
    std::vector<double> inputs(100000);
    std::generate(inputs.begin(), inputs.end(), [&](){ return unif(re); });

    double mean;
    for (double input : inputs) {
        rolling_average_.push_back(input);
        mean = rolling_average_.mean();
    }
}

TEST_P(TestParametricRollingAverage, TestMean1) {
    double lower_bound = 0;
    double upper_bound = 100;

    std::uniform_real_distribution<double> unif(lower_bound,
                                                upper_bound);
    std::default_random_engine re;
    std::vector<double> inputs(1000000);
    std::generate(inputs.begin(), inputs.end(), [&](){ return unif(re); });

    double mean;
    for (double input : inputs) {
        rolling_average_.add(input);
        mean = rolling_average_.mean2();
    }
}

INSTANTIATE_TEST_CASE_P(
        BenchmarkTests,
        TestParametricRollingAverage,
        ::testing::Values(
                1, 10, 100, 1000, 10000
        ));