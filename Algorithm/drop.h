#ifndef PANLIB_ALGORITHM_DROP
#define PANLIB_ALGORITHM_DROP

#include <utility>
#include <cstddef>

template<typename Range>
struct Drop{
private:
	Range range;

public:
	Drop(Range r,std::size_t s) : range(std::move(r)){
		while(s){
			range.pop_front();
			s--;
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

#endif
