#ifndef PANLIB_ALGORITHM_REPEAT
#define PANLIB_ALGORITHM_REPEAT

#include <utility>

#include "../Range/range.h"

namespace panlib{
namespace algorithm{

template<typename T>
struct Repeat : range::operators::dummy_t{
private:
	T value;

public:
	Repeat(T v) : value(std::move(v)){
	}

	void pop_front(){
	}

	T front(){
		return value;
	}

	bool empty() const{
		return false;
	}
};

} //namespace algorithm
} //namespace panlib


#endif
