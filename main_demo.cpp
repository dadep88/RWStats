//
// Created by Davide Pilastro on 10/25/23.
//

#include <array>
#include <cmath>
#include <fstream>
#include <random>

#include "rw_stats.h"

using namespace  RWStats;

static constexpr size_t samples = 1e5;

int main(int argc, char *argv[]) {
  double lower_bound = -0.1;
  double upper_bound = 0.1;
  std::uniform_real_distribution<double> unif1(lower_bound, upper_bound);
  std::uniform_real_distribution<double> unif2(lower_bound * 3,
                                               upper_bound * 3);
  std::default_random_engine re;
  RollingWindowedStats<double> rolling_stats(100);

  std::ofstream output_file("output.csv");
  for (size_t idx = 0; idx < samples; idx++) {
    double t = idx / 1000.0;
    double y = std::sin(t * M_2_PI * 0.5) +
               std::cos(t * M_2_PI * 0.2 + M_PI_4) +
               std::sin(t * M_2_PI * 0.03 + M_PI_2) + unif1(re);
    if (idx > 40000) y += unif2(re);
    rolling_stats.push_back(y);
    auto d = rolling_stats.std_dev();
    output_file << t << ";" << y << ";" << rolling_stats.mean() << ";"
                << rolling_stats.std_dev() << std::endl;
  }
  output_file.close();

  return 0;
}
