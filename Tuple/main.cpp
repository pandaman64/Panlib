#include "fold.h"

#include <iostream>

int main(){
	auto tuple = std::make_tuple(true,false,3,5);

	std::cout << panlib::tuple::all(tuple);
	std::cout << panlib::tuple::any(tuple) << std::endl;
}

