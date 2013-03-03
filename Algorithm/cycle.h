#ifndef PANLIB_ALGORITHM_CYCLE
#define PANLIB_ALGORITHM_CYCLE

#include <utility>
#include <cassert>

namespace panlib{
namespace algorithm{

template<typename ForwardRange>
struct Cycle{
private:
	ForwardRange original_range,now_range;

public:
	Cycle(ForwardRange r) : original_range(r),now_range(std::move(r)){
		assert(!original_range.empty());
	}

	void pop_front(){
		now_range.pop_front();
	}

	auto front()
	->decltype(now_range.front()){
		if(now_range.empty()){
			now_range = original_range;
		}

		return now_range.front();
	}

	bool empty() const{
		return false;
	}
};

} //namespace algorithm
} //namespace panlib


#endif
