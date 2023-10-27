#ifndef ROLLING_STATS_LIBRARY_H
#define ROLLING_STATS_LIBRARY_H

#include <boost/circular_buffer.hpp>
#include <limits>
#include <numeric>

template <typename T>
class RollingAverage : private boost::circular_buffer<T> {
  using Buffer = boost::circular_buffer<T>;
  T value_;

 public:
  RollingAverage(size_t window_size)
      : boost::circular_buffer<T>(window_size), value_(0) {}

  T value() { return value_; }
  using Buffer::begin;
  using Buffer::capacity;
  using Buffer::empty;
  using Buffer::end;
  using Buffer::size;

  void push_back(T input) {
    value_ *= size();
    value_ += input;
    if (size() == capacity()) value_ -= (*this)[0];
    Buffer::push_back(input);
    value_ /= size();
  }

 private:
  using Buffer::pop_front;
};

#endif  // ROLLING_STATS_LIBRARY_H
