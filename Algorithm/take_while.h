#ifndef PANLIB_ALGORITHM_TAKE_WHILE
#define PANLIB_ALGORITHM_TAKE_WHILE

#include <utility>

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
struct TakeWhile{
private:
	Range range;
	Pred pred;
	bool okay;

public:
	TakeWhile(Range r,Pred p) : range(std::move(r)),pred(std::move(p)),okay(false){
		okay = pred(range.front());
	}

	void pop_front(){
		range.pop_front();
		okay = pred(range.front());
	}

	auto front()
	->decltype(range.front()){
		return range.front();
	}

	bool empty() const{
		return range.empty() || !okay;
	}
};

} //namespace algorithm
} //namespace panlib


#endif
