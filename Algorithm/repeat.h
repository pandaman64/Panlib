#ifndef PANLIB_ALGORITHM_REPEAT
#define PANLIB_ALGORITHM_REPEAT

#include <utility>


namespace panlib{
namespace algorithm{

template<typename T>
struct Repeat{
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
