#ifndef ROLLING_STATS_LIBRARY_H
#define ROLLING_STATS_LIBRARY_H

#include <boost/circular_buffer.hpp>
#include <numeric>

namespace RWStats {
/// \brief Template class for rolling windowed statistics.
/// Capable to compute rolling windowed mean, variance and standard deviation of windowed
/// data series. \tparam T data type of the data
template <typename T>
class RollingWindowStats : private boost::circular_buffer<T> {
  using Buffer = boost::circular_buffer<T>;
  /// Current rolling mean value
  T mean_;
  /// Previous rolling mean value
  T pre_mean_;
  /// Current square rolling mean value
  T mean2_;
  /// Previous square rolling mean value
  T prev_mean2_;

 public:
  /// Default ctor
  /// \param window_size Rolling statistics window sizes
  RollingWindowStats(size_t window_size) noexcept
      : boost::circular_buffer<T>(window_size),
        mean_(0),
        pre_mean_(0),
        mean2_(0),
        prev_mean2_(0) {}

  /// \return Rolling windowed mean
  T mean() const noexcept { return mean_; }

  /// \return Rolling windowed variance
  T variance() const noexcept { return mean2_ - mean_ * mean_; }

  /// \return Rolling windowed standard deviation
  T std_dev() const noexcept { return sqrt(variance()); }

  using Buffer::begin;
  using Buffer::capacity;
  using Buffer::empty;
  using Buffer::end;
  using Buffer::size;

  /// Add data to the rolling statistics
  void push_back(T input) noexcept {
    pre_mean_ = mean_;
    prev_mean2_ = mean2_;
    mean_ *= size();
    mean2_ *= size();
    mean_ += input;
    mean2_ += input * input;
    if (size() == capacity()) {
      T last_value = (*this)[0];
      mean_ -= last_value;
      mean2_ -= last_value * last_value;
    }
    Buffer::push_back(input);
    mean_ /= size();
    mean2_ /= size();
  }

 private:
  using Buffer::pop_front;
};
}  // namespace RollingWindowStats

#endif  // ROLLING_STATS_LIBRARY_H
