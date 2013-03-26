#ifndef PANLIB_RANGE_IO
#define PANLIB_RANGE_IO

#include <iostream>

namespace panlib{
namespace range{

template<typename Range>
void print_range(Range &&range){
	if(range.empty()){
		return;
	}

	std::cout << range.front();
	range.pop_front();
	while(!range.empty()){
		std::cout << ',' << range.front();
		range.pop_front();
	}

	std::cout << std::endl;
}

} //namespace range
} //namespace panlib

#endif

