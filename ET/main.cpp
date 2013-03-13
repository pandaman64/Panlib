#include "expression.h"
#include "io.h"
#include "default_context.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <tuple>
#include <cstdlib>

#include "cxxabi.h"

template<typename>
struct type{};
std::string demangle(char const* s){
	auto str = abi::__cxa_demangle(s,0,0,nullptr);
	std::string ret = str;
	std::free(str);
	return ret;
}
template<typename T>
void print_type(T &&v){
	std::cout << demangle(typeid(type<T>).name()) << std::endl;
}

int main(){
	using namespace panlib::ET;
	using namespace panlib::ET::operators;
	using std::get;

	auto expr = lit(3) + 6 - 7;
	print_type(expr);
	print_expr(expr);

	default_context ctx;
	std::cout << evaluate(lit(5)+6-2,ctx) << std::endl;

	return 0;
}
