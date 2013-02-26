#ifndef PANLIB_ALGORITHM_TAKE
#define PANLIB_ALGORITHM_TAKE

#include <cassert>
#include <type_traits>

namespace panlib{
namespace algorithm{

template<typename Range>
struct Take{
private:
	Range range;
	std::size_t size;

public:
	Take(Range r,std::size_t s) : range(std::move(r)),size(s){
	}

	void pop_front(){
		assert(size);
		range.pop_front();
		size--;
	}

	auto front()
	->decltype(range.front()){
		return range.front();
	}

	bool empty() const{
		return !size || range.empty();
	}
};

} //namespace algorithm
} //namespace panlib

#endif
