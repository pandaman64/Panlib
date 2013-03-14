#ifndef PANLIB_ET_UNARY_OPEARATOR
#define PANLIB_ET_UNARY_OPEARATOR

#include <string>
#include <sstream>
#include <utility>
#include <tuple>
#include <cstddef>

#include "expression_base.h"
#include "tag.h"

#define UNARY_OP(name) \
template<typename T>\
struct name : unary_operator_base<name<T>,T>{\
	using base = unary_operator_base<name,T>;\
	using tag = tag::unary_operator::name;\
	char const* expr_name = #name;\
	template<typename U>\
	name(U &&v) : base(std::forward<U>(v)){\
	}\
}

namespace panlib{
namespace ET{
namespace unary_operator{
	template<typename Derived,typename T>
	struct unary_operator_base : expression_base<unary_operator_base<Derived,T>>{
	private:
		T value;

	public:
		using tuple_type = std::tuple<T&>;
		using const_tuple_type = std::tuple<T const&>;

		template<typename U>
		unary_operator_base(U &&v) : value(std::forward<U>(v)){
		}

		tuple_type as_tuple(){
			return std::tie(value);
		}
		const_tuple_type const as_tuple() const{
			return std::tie(value);
		}
	};

	
	UNARY_OP(plus); //unary +
	UNARY_OP(negate); //unary -
	UNARY_OP(dereference); //unary *
	UNARY_OP(complement); //unary ~
	UNARY_OP(address_of); //unary &
	UNARY_OP(logical_not); //unary !
	UNARY_OP(prefix_increment); //unary pre ++
	UNARY_OP(prefix_decrement); //unary pre --
	UNARY_OP(postfix_increment); //unary post ++
	UNARY_OP(postfix_decrement); //unary post --
} //namespace unary_operator 

	template<typename Derived,typename T>
	struct terminal_type<unary_operator::unary_operator_base<Derived,T>>{
		typedef typename terminal_type<Derived>::type type;
	};

} //namespace ET
} //namespace panlib

#undef UNARY_OP

#endif

