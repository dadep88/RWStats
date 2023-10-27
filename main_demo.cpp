//
// Created by Davide Pilastro on 10/25/23.
//

#include <array>
#include <cmath>
#include <fstream>
#include <random>

#include "rolling_stats.h"

static constexpr size_t samples = 1e5;

int main(int argc, char *argv[]) {
  int count;

  double lower_bound = -0.1;
  double upper_bound = 0.1;
  std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std::default_random_engine re;
  std::array<double, samples> t;
  std::array<double, samples> y;
  for (size_t idx = 0; idx < samples; idx++) {
    t[idx] = idx / 1000.0;
    y[idx] = std::sin(t[idx] * M_2_PI * 0.5) +
             std::cos(t[idx] * M_2_PI * 0.2 + M_PI_4) +
             std::sin(t[idx] * M_2_PI * 0.03 + M_PI_2);
  }
  std::for_each(y.begin(), y.end(),
                [&unif, &re](double &value) { value += unif(re); });

  std::ofstream output_file("output.csv");

  for (size_t idx = 0; idx < samples; idx++)
    output_file << t[idx] << ";" << y[idx] << std::endl;

  // Close the file
  output_file.close();

  return 0;
}
