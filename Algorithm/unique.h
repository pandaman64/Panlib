#ifndef PANLIB_ALGORITHM_UNIQUE
#define PANLIB_ALGORITHM_UNIQUE

#include <type_traits>

#include "equal_to.h"

namespace panlib{
namespace algorithm{

template<typename ForwardRange,typename Pred>
struct Unique{
private:
	ForwardRange range;
	Pred pred;

public:
	Unique(ForwardRange r,Pred p = Pred()) : range(std::move(r)),pred(std::move(p)){
	}

	void pop_front(){
		auto copied_range = range;
		copied_range.pop_front();
		while(!copied_range.empty() && pred(copied_range.front(),range.front())){
			range.pop_front();
			copied_range.pop_front();
		}
		range.pop_front();
	}

	auto front()
	->decltype(range.front()){
		return range.front();
	}

	bool empty() const{
		return range.empty();
	}
};

} //namespace algorithm
} //namespace panlib

#endif
