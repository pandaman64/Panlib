#ifndef PANLIB_ALGORITHM_DROP_FUNCTIONAL
#define PANLIB_ALGORITHM_DROP_FUNCTIONAL

#include <cstddef>
#include <utility>

#include "../drop.h"

namespace panlib{
namespace algorithm{

template<typename T>
Drop<T> drop(T range,std::size_t size){
	return { std::move(range),size };
}

} //namespace algorithm
} //namespace panlib

#endif
