#ifndef PANLIB_ALGORITHM_FIND
#define PANLIB_ALGORITHM_FIND

#include <type_traits>

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
struct Find{
private:
	Range range;
	Pred pred;

public:
	Find(Range r,Pred p) : range(std::move(r)),pred(std::move(p)){
		while(!range.empty() && !pred(range.front())){
			range.pop_front();
		}
	}

	void pop_front(){
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
