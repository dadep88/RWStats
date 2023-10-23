#ifndef ROLLING_STATS_LIBRARY_H
#define ROLLING_STATS_LIBRARY_H

#include <boost/circular_buffer.hpp>
#include<numeric>
#include<limits>


template<typename T>
class RollingAverage : private boost::circular_buffer<T>{
    using Buffer = boost::circular_buffer<T>;
    T mean_;
public:
    RollingAverage(size_t window_size) :
            boost::circular_buffer<T>(window_size),
                    mean_(){}

    T value() {
        return std::accumulate(begin(), end(), 0)/ size();
    }
    using Buffer::begin;
    using Buffer::end;
    using Buffer::size;
    using Buffer::capacity;
    using Buffer::push_back;
    using Buffer::pop_front;

    void add(T input){
        if(size() < capacity()){
            mean_ = (mean_ * size() + input)/ (size() + 1);
        }
        else{
        T data = (*this)[1];
        mean_ =  ( mean_ * size() - data + input) / size();
        }
        push_back();
    }

    T mean2() const noexcept{
        return mean_;
    }
};

#endif //ROLLING_STATS_LIBRARY_H
