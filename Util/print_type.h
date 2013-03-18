#ifndef PANLIB_UTIL_PRINT_TYPE
#define PANLIB_UTIL_PRINT_TYPE

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include "cxxabi.h"

namespace panlib{
namespace util{

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
template<typename T>
void print_type(){
	std::cout << demangle(typeid(type<T>).name()) << std::endl;
}
} //namespace util
} //namespace panlib

#endif

