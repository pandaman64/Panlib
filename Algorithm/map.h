#ifndef PANLIB_ALGORITHM_MAP
#define PANLIB_ALGORTIHM_MAP

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
class Map{
private:
	Range range;
	Pred predicate;
	
public:
	Map(Range r,Pred p) : range(r),predicate(p){
	}

	void pop_front(){
		range.pop_front();
	}

	auto front()
	->decltype(predicate(range.front())){
		return predicate(range.front());
	}

	bool empty() const{
		return range.empty();
	}
};

} //namespace algorithm
} //namespace panlib

#endif
