#include "algorithm.h"

#include <iostream>

template<typename Range>
void print_range(Range range){
	while(!range.empty()){
		std::cout << range.front() << std::endl;
		range.pop_front();
	}
}

int main(){
	using namespace panlib::algorithm;

	{
		auto range = take_while(
			map(
			iota(),
			[](int i){return i*i;}
		),
			[](int i){return i < 1000;}
		);

		print_range(range);
	}
	
	{
		auto range = take(
			cycle(iota(1,3)),
			10
			);

		print_range(range);
	}

	{
		auto range = take(
			repeat(5),
			10
			);

		print_range(range);
	}

	return 0;
}
