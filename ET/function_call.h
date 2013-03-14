#ifndef PANLIB_ET_NARY_OPERATOR
#define PANLIB_ET_NARY_OPERATOR

#include <utility>
#include <tuple>

#include "tag.h"

namespace panlib{
namespace ET{

	template<typename Derived>
	struct expression_base;

namespace function_call{
	template<typename Callee,typename ...Args>
	struct function : expression_base<function<Callee,Args...>>{
		using tuple_type = std::tuple<Args&...>;
		using const_tuple_type = std::tuple<Args const&...>;
		using tag = tag::function_call::function;
		
		char const* expr_name = "function_call";

		Callee callee;
		std::tuple<Args...> arguments;
		
		template<typename T,typename ...As>
		function(T && c,As &&...as) : callee(std::forward<T>(c)),arguments(std::forward<As>(as)...){
		}

		tuple_type as_tuple(){
			return arguments;
		}
		const_tuple_type const as_tuple() const{
			return arguments;
		}
	};		
} //namespace function_call
} //namespace ET
} //namespace panlib
#endif

