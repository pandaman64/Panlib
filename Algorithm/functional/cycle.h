#ifndef PANLIB_ALGORITHM_CYCLE_FUNCTIONAL
#define PANLIB_ALGORITHM_CYCLE_FUNCTIONAL

#include "../cycle.h"


namespace panlib{
namespace algorithm{

template<typename ForwardRange>
Cycle<ForwardRange> cycle(ForwardRange range){
	return { std::move(range) };
}

} //namespace algorithm
} //namespace panlib


#endif
