#ifndef PANLIB_AlGORITHM_FILTER_FUNCTIONAL
#define PANlIB_ALGORITHM_FILTER_FUNCTIONAL

#include <utility>

#include "../filter.h"

namespace panlib{
namespace algorithm{

template<typename T,typename Pred>
Filter<T,Pred> filter(T range,Pred pred){
	return { std::move(range),std::move(pred) };
}

} //namespace algorithm
} //namespace panlib

#endif
