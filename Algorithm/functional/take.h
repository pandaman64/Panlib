#ifndef PANLIB_ALGORITHM_TAKE_FUNCTIONAL
#define PANLIB_ALGORITHM_TAKE_FUNCTIONAL

#include "../take.h"

namespace panlib{
namespace algorithm{

template<typename T>
Take<T> take(T range,std::size_t size){
	return { std::move(range),size };
}

} //namespace algorithm
} //namespace panlib

#endif
