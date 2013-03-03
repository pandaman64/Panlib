#ifndef PANLIB_AlGORITHM_FILTER
#define PANlIB_ALGORITHM_FILTER

#include <utility>

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
class Filter{
private:
	Range range;
	Pred pred;
	
public:
	Filter(Range r,Pred p) : range(std::move(r)),pred(std::move(p)){
		while(!range.empty() && !pred(range.front())){
			range.pop_front();
		}
	}

	void pop_front(){
		do{
			range.pop_front();
		}while(!range.empty() && !pred(range.front()));
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
