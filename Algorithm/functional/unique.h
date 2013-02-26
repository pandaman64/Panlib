#ifndef PANLIB_ALGORITHM_UNIQUE_FUNCTIONAL
#define PANLIB_ALGORITHM_UNIQUE_FUNCTIONAL

#include "../unique.h"

namespace panlib{
namespace algorithm{

template<typename ForwardRange,typename Pred = panlib::algorithm::equal_to>
Unique<ForwardRange,Pred> unique(ForwardRange range,Pred pred = Pred()){
	return { std::move(range),std::move(pred) };
}

} //namespace algorithm
} //namespace panlib

#endif
