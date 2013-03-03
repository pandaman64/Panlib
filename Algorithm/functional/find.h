#ifndef PANLIB_ALGORITHM_FIND_FUNCTIONAL
#define PANLIB_ALGORITHM_FIND_FUNCTIONAL

#include <utility>

#include "../find.h"

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
Find<Range,Pred> find(Range range,Pred pred){
	return { std::move(range),std::move(pred) };
}

} //namespace algorithm
} //namespace panlib

#endif
