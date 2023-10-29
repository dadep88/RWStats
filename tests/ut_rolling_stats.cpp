//
// Created by Davide Pilastro on 10/21/23.
//

#include <gtest/gtest.h>

#include <random>

#include "rolling_stats.h"

using namespace RWStats;

template <template <class> class V, class T>
T mean(const V<T> container) {
  return std::accumulate(container.begin(), container.end(),
                         static_cast<T>(0)) /
         container.size();
}

TEST(TestRollingMean, Test1Value) {
  auto ra = RollingWindowStats<double>(5);
  ra.push_back(3.0);
  ASSERT_DOUBLE_EQ(ra.mean(), mean(ra));
}

TEST(TestRollingMean, Test2Values) {
  auto ra = RollingWindowStats<double>(5);
  ra.push_back(3.0);
  ra.push_back(5.0);
  ASSERT_DOUBLE_EQ(ra.mean(), mean(ra));
}

TEST(TestRollingMean, TestRolling) {
  auto ra = RollingWindowStats<double>(3);
  ra.push_back(3.0);
  ra.push_back(5.0);
  ra.push_back(2.0);
  ra.push_back(3.0);
  ra.push_back(5.0);
  ra.push_back(1.0);
  ASSERT_DOUBLE_EQ(ra.mean(), mean(ra));
}

class TestParametricRollingMean : public ::testing::TestWithParam<size_t> {
 protected:
  RollingWindowStats<double> ra_;

  TestParametricRollingMean() : ra_(GetParam()) {}
};

TEST_P(TestParametricRollingMean, TestMean) {
  double lower_bound = 0;
  double upper_bound = 100;

  std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std::default_random_engine re;
  std::vector<double> inputs(100000);
  std::generate(inputs.begin(), inputs.end(), [&]() { return unif(re); });

  for (double input : inputs) {
    ra_.push_back(input);
    ASSERT_NEAR(ra_.mean(), mean(ra_), 1e-9);
  }
}

INSTANTIATE_TEST_SUITE_P(BenchmarkTests, TestParametricRollingMean,
                         ::testing::Values(1, 10, 100, 1000, 10000));