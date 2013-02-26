#ifndef PANLIB_ALGORITHM_MAP
#define PANLIB_ALGORTIHM_MAP

#include <type_traits>

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
class Map{
private:
	Range range;
	Pred pred;
	
public:
	Map(Range r,Pred p) : range(std::move(r)),pred(std::move(p)){
	}

	void pop_front(){
		range.pop_front();
	}

	auto front()
	->decltype(pred(range.front())){
		return pred(range.front());
	}

	bool empty() const{
		return range.empty();
	}
};

} //namespace algorithm
} //namespace panlib

#endif
