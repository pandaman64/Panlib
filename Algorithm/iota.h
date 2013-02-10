#ifndef PANLIB_ALGORITHM_IOTA
#define PANLIB_ALGORITHM_IOTA

#include <utility>
#include <cassert>
#include <cstddef>

namespace panlib{
namespace algorithm{

template<typename T>
struct IotaBase{
private:
	T value,end,step;

public:
	IotaBase(T b,T e,T s) : value(std::move(b)),end(std::move(e)),step(std::move(s)){
	}

	void pop_front(){
		assert(!empty());
		value += step;
	}

	T& front(){
		return value;
	}

	bool empty() const{
		return value > end;
	}
};

typedef IotaBase<int> Iota;

Iota iota(int b,int e = INT_MAX,int s = 1){
	return Iota(b,e,s);
}

} //namespace algorithm
} //namespace panlib

#endif
