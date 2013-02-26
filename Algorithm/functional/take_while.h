#ifndef PANLIB_ALGORITHM_TAKE_WHILE_FUNCTIONAL
#define PANLIB_ALGORITHM_TAKE_WHILE_FUNCTIONAL

#include "../take_while.h"

namespace panlib{
namespace algorithm{

template<typename T,typename Pred>
TakeWhile<T,Pred> take_while(T range,Pred pred){
	return { std::move(range),std::move(pred) };
}

} //namespace algorithm
} //namespace panlib


#endif
