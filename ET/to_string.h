#ifndef PANLIB_ET_TO_STRING
#define PANLIB_ET_TO_STRING

#include <sstream>
#include <string>

#include "expression_base.h"
#include "../Tuple/io.h"
#include "../Tuple/transform.h"

//workaround for mingw
#include <type_traits>

namespace panlib{
namespace ET{
namespace detail{
	//workaround for mingw
	template<typename T>
	std::string to_string(T &&value,typename std::enable_if<!std::is_base_of<expression_root,typename std::remove_reference<T>::type>{}>::type* = nullptr){
		std::stringstream s;
		s << value;
		return s.str();
	}

	struct to_string_wrapper{
		template<typename T>
		std::string operator ()(T &&value){
			//using std::to_string; //workaround for mingw
			return to_string(value);
		}
	};
} //namespace detail

template<typename Derived>
std::string to_string(expression_base<Derived> &expr){
	std::stringstream stream;
	stream << expr.name();
	tuple::print_tuple(stream,tuple::transform(expr.as_term().as_tuple(),detail::to_string_wrapper()));
	return stream.str();	
}

} //namespace ET
} //namespace panlib

#endif

