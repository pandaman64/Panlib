#ifndef PANLIB_ALGORITHM_REPEAT_FUNCTIONAL
#define PANLIB_ALGORITHM_REPEAT_FUNCTIONAL

#include "../repeat.h"

namespace panlib{
namespace algorithm{

template<typename T>
Repeat<T> repeat(T value){
	return { std::move(value) };
}

} //namespace algorithm
} //namespace panlib


#endif
