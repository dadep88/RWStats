#ifndef ROLLING_STATS_LIBRARY_H
#define ROLLING_STATS_LIBRARY_H

#include <boost/circular_buffer.hpp>
#include <limits>
#include <numeric>

template <typename T>
class RollingStats : private boost::circular_buffer<T> {
  using Buffer = boost::circular_buffer<T>;
  T mean_;
  T std_;

 public:
  RollingStats(size_t window_size)
      : boost::circular_buffer<T>(window_size), mean_(0) {}

  T mean() { return mean_; }
  T std() { return std_; }
  using Buffer::begin;
  using Buffer::capacity;
  using Buffer::empty;
  using Buffer::end;
  using Buffer::size;

  void push_back(T input) {
    mean_ *= size();
    mean_ += input;
    if (size() == capacity()) mean_ -= (*this)[0];
    Buffer::push_back(input);
    mean_ /= size();
  }

 private:
  using Buffer::pop_front;
};

#endif  // ROLLING_STATS_LIBRARY_H
