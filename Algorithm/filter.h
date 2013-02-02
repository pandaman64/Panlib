#ifndef PANLIB_AlGORITHM_FILTER
#define PANlIB_ALGORITHM_FILTER

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
class Filter{
private:
	Range range;
	Pred predicate;
	
public:
	Filter(Range r,Pred p) : range(r),predicate(p){
		while(!predecate(range.front()){
			range.pop_front();
		}
	}

	void pop_front(){
		while(!predecate(range.front()){
			range.pop_front();
		}
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
