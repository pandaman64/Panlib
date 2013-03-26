#ifndef PANLIB_ET_BINARY_OPEARATOR
#define PANLIB_ET_BINARY_OPEARATOR

#include <string>
#include <sstream>
#include <utility>
#include <tuple>
#include <cstddef>

#include "expression_base.h"
#include "tag.h"

#define BINARY_OP(name) \
template<typename Left,typename Right>\
struct name : binary_operator_base<name<Left,Right>,Left,Right>{\
	using base = binary_operator_base<name,Left,Right>;\
	using tag = tag::binary_operator::name;\
	char const* const expr_name = #name;\
	template<typename L,typename R>\
	constexpr name(L &&l,R &&r) : base(std::forward<L>(l),std::forward<R>(r)){\
	}\
}

namespace panlib{
namespace ET{
namespace binary_operator{
	template<typename Derived,typename Left,typename Right>
	struct binary_operator_base : expression_base<binary_operator_base<Derived,Left,Right>>{
	private:
		Left left;
		Right right;

	public:
		using tuple_type = std::tuple<Left&,Right&>;
		using const_tuple_type = std::tuple<Left const&,Right const&>;

		template<typename L,typename R>
		constexpr binary_operator_base(L &&l,R &&r) : left(std::forward<L>(l)),right(std::forward<R>(r)){
		}

		tuple_type as_tuple(){
			return std::tie(left,right);
		}
		const_tuple_type const as_tuple() const{
			return std::tie(left,right);
		}
	};

	//numeric operators
	BINARY_OP(plus); //binary +
	BINARY_OP(minus); //binary -
	BINARY_OP(multiple); //binary *
	BINARY_OP(divide); //binary / 
	BINARY_OP(module); //binary %
	BINARY_OP(left_shift); //binary <<
	BINARY_OP(right_shift); //binary >>

	//compare operators
	BINARY_OP(less); //binary <
	BINARY_OP(greater); //binary >
	BINARY_OP(less_equal); //binary <=
	BINARY_OP(greater_equal); //binary >=
	BINARY_OP(equal_to); //binary ==
	BINARY_OP(not_equal_to); //binary !=

	//logical operators
	BINARY_OP(logical_or); //binary ||
	BINARY_OP(logical_and); //binary &&
	BINARY_OP(bitwise_or); //binary |
	BINARY_OP(bitwise_and); //binary &
	BINARY_OP(bitwise_xor); //binary ^
	
	//assign operators
	BINARY_OP(assign); //binary =
	BINARY_OP(plus_assign); //binary +=
	BINARY_OP(minus_assign); //binary -=
	BINARY_OP(multiple_assign); //binary *=
	BINARY_OP(divide_assign); //binary /=
	BINARY_OP(module_assign); //binary %=
	BINARY_OP(left_shift_assign); //binary <<=
	BINARY_OP(right_shift_assign); //binary >>=
	BINARY_OP(bitwise_or_assign); //binary |=
	BINARY_OP(bitwise_and_assign); //binary &=
	BINARY_OP(bitwise_xor_assign); //binary ^=

	//other operators
	BINARY_OP(comma); //binary , 
	BINARY_OP(member_pointer); //binary ->*
	BINARY_OP(subscription); //binary []
} //namespace binary_operator 

	template<typename Derived,typename ...Args>
	struct terminal_type<binary_operator::binary_operator_base<Derived,Args...>>{
		typedef typename terminal_type<Derived>::type type;
	};

} //namespace ET
} //namespace panlib

#undef BINARY_OP

#endif

