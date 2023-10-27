//
// Created by Davide Pilastro on 10/21/23.
//

#include <gtest/gtest.h>

#include <random>

#include "rolling_stats.h"

template <template <class> class V, class T>
T mean(const V<T> container) {
  return std::accumulate(container.begin(), container.end(),
                         static_cast<T>(0)) /
         container.size();
}

TEST(TestRollingAverage, Test1Value) {
  auto ra = RollingAverage<double>(5);
  ra.push_back(3.0);
  ASSERT_DOUBLE_EQ(ra.value(), mean(ra));
}

TEST(TestRollingAverage, Test2Values) {
  auto ra = RollingAverage<double>(5);
  ra.push_back(3.0);
  ra.push_back(5.0);
  ASSERT_DOUBLE_EQ(ra.value(), mean(ra));
}

TEST(TestRollingAverage, TestRolling) {
  auto ra = RollingAverage<double>(3);
  ra.push_back(3.0);
  ra.push_back(5.0);
  ra.push_back(2.0);
  ra.push_back(3.0);
  ra.push_back(5.0);
  ra.push_back(1.0);
  ASSERT_DOUBLE_EQ(ra.value(), mean(ra));
}

class TestParametricRollingAverage : public ::testing::TestWithParam<size_t> {
 protected:
  RollingAverage<double> ra_;

  TestParametricRollingAverage() : ra_(GetParam()) {}
};

TEST_P(TestParametricRollingAverage, TestMean) {
  double lower_bound = 0;
  double upper_bound = 100;

  std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std::default_random_engine re;
  std::vector<double> inputs(100000);
  std::generate(inputs.begin(), inputs.end(), [&]() { return unif(re); });

  for (double input : inputs) {
    ra_.push_back(input);
    ASSERT_NEAR(ra_.value(), mean(ra_), 1e-9);
  }
}

INSTANTIATE_TEST_CASE_P(BenchmarkTests, TestParametricRollingAverage,
                        ::testing::Values(1, 10, 100, 1000, 10000));