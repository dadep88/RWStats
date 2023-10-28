#ifndef ROLLING_STATS_LIBRARY_H
#define ROLLING_STATS_LIBRARY_H

#include <boost/circular_buffer.hpp>
#include <limits>
#include <numeric>

template <typename T>
class RollingStats : private boost::circular_buffer<T> {
  using Buffer = boost::circular_buffer<T>;
  T mean_;
  T mean0_;
  T mean_square_;
  T mean_square0_;

 public:
  RollingStats(size_t window_size)
      : boost::circular_buffer<T>(window_size),
        mean_(0),
        mean0_(0),
        mean_square_(0),
        mean_square0_(0) {}

  T mean() { return mean_; }
  T variance() { return mean_square_ - pow(mean_, 2.0); }
  T std_dev() { return sqrt(variance()); }
  using Buffer::begin;
  using Buffer::capacity;
  using Buffer::empty;
  using Buffer::end;
  using Buffer::size;

  void push_back(T input) {
    mean0_ = mean_;
    mean_square0_ = mean_square_;
    mean_ *= size();
    mean_square_ *= size();
    mean_ += input;
    mean_square_ += pow(input, 2.0);
    if (size() == capacity()) {
      mean_ -= (*this)[0];
      mean_square_ -= pow((*this)[0], 2.0);
    }
    Buffer::push_back(input);
    mean_ /= size();
    mean_square_ /= size();
  }

 private:
  using Buffer::pop_front;
};

#endif  // ROLLING_STATS_LIBRARY_H
