#ifndef PANLIB_ALGORITHM_RETRO
#define PANLIB_ALGORITHM_RETRO

#include <utility>

namespace panlib{
namespace algorithm{

template<typename BidirectionalRange>
struct Retro{
private:
	BidirectionalRange range;

public:
	Retro(BidirectionalRange r) : range(std::move(r)){
	}

	void pop_front(){
		range.pop_back();
	}

	auto front()
	->decltype(range.back()){
		return range.back();
	}

	bool empty() const{
		return range.empty();
	}
};

} //namespace algorithm
} //namespace panlib

#endif
