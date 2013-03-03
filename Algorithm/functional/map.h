#ifndef PANLIB_ALGORITHM_MAP_FUNCTIONAL
#define PANLIB_ALGORTIHM_MAP_FUNCTIONAL

#include <utility>

#include "../map.h"

namespace panlib{
namespace algorithm{

template<typename T,typename Pred>
Map<T,Pred> map(T range,Pred pred){
	return { std::move(range),std::move(pred) };
}

} //namespace algorithm
} //namespace panlib

#endif
