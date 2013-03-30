#include "fold.h"
#include "tuple.h"
#include "io.h"

#include <iostream>

int main(){
	using std::get;
	using namespace panlib::tuple;
	auto tuple = panlib::tuple::make_tuple(true,false,3,5);

	std::cout << tuple << std::endl;
	std::cout << panlib::tuple::all(tuple);
	std::cout << panlib::tuple::any(tuple) << std::endl;
}

