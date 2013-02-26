#ifndef PANLIB_ALGORITHM_IOTA_FUNCTIONAL
#define PANLIB_ALGORITHM_IOTA_FUNCTIONAL

#include <limits>

#include "../iota.h"

namespace panlib{
namespace algorithm{

template<typename T = int>
IotaBase<T> iota(int b = 0,int e = std::numeric_limits<T>::max(),int s = 1){
	return { b,e,s };
}

} //namespace algorithm
} //namespace panlib

#endif
