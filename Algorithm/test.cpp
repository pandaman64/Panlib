#include "../Range/range.h"
#include "../Tuple/io.h"
#include "algorithm.h"

#include <iostream>
#include <tuple>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

#include "../Range/io.h"

int main(){
	using namespace panlib::range;
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

	{
		auto range = take(
			zip(
				iota(),
				map(iota(),[](int i){return i*i;})
				)
				,10);

		print_range(range);
	}

	{
		std::vector<int> vec(10,0);
		std::mt19937 mt(static_cast<unsigned int>(std::time(nullptr)));
		std::uniform_int_distribution<> gen(1,6);
		std::generate(vec.begin(),vec.end(),[&](){return gen(mt);});
		
		auto range = zip(
			iota(),
			all(vec)
		);

		print_range(range);
	}

	return 0;
}

