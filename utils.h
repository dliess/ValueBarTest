#ifndef UTILS_H
#define UTILS_H

#include <limits>

template<typename T>
void stayInRange(T& rValue, T min, T max)
{
    if(rValue <= min || rValue == std::numeric_limits<T>::max())
        rValue = min;
    if(rValue > max)
        rValue = max;
}


#endif