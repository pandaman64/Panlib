#ifndef EXPRESSION_BUILDER
#define EXPRESSION_BUILDER

#include <utility>

#include "expression_base.h"

#define UNARY_OP(op,name)\
	template<typename T>\
	unary_operator::name<T> operator op(T &&v){\
		return { std::forward<T>(v) };\
	}

#define BINARY_OP(op,name)\
	template<typename Left,typename Right>\
	binary_operator::name<Left,Right> operator op(Left &&left,Right &&right){\
		return { std::forward<Left>(left),std::forward<Right>(right) };\
	}

namespace panlib{
namespace ET{
namespace operators{
	UNARY_OP(+,plus)
	UNARY_OP(-,negate)
	UNARY_OP(*,dereference)
	UNARY_OP(~,complement)
	UNARY_OP(&,address_of)
	UNARY_OP(!,logical_not)
	UNARY_OP(++,prefix_increment)
	UNARY_OP(--,prefix_decrement)
	template<typename T>
	unary_operator::postfix_increment<T> operator ++(T &&v,int){
		return { std::forward<T>(v) };
	}
	template<typename T>
	unary_operator::postfix_decrement<T> operator --(T &&v,int){
		return { std::forward<T>(v) };
	}

	//numeric operators
	BINARY_OP(+,plus)
	BINARY_OP(-,minus)
	BINARY_OP(*,multiple)
	BINARY_OP(/,divide)
	BINARY_OP(%,module)
	BINARY_OP(<<,left_shift)
	BINARY_OP(>>,right_shift)

	//compare operators
	BINARY_OP(<,less)
	BINARY_OP(>,greater)
	BINARY_OP(<=,less_equal)
	BINARY_OP(>=,greater_equal)
	BINARY_OP(==,equal_to)
	BINARY_OP(!=,not_equal_to)

	//logical operators
	BINARY_OP(||,logical_or)
	BINARY_OP(&&,logical_and)
	BINARY_OP(|,bitwise_or)
	BINARY_OP(&,bitwise_and)
	BINARY_OP(^,bitwise_xor)
	
	//assign operators
	BINARY_OP(+=,plus_assign)
	BINARY_OP(-=,minus_assign)
	BINARY_OP(*=,multiple_assign)
	BINARY_OP(/=,divide_assign)
	BINARY_OP(%=,module_assign)
	BINARY_OP(<<=,left_shift_assign)
	BINARY_OP(>>=,right_shift_assign)
	BINARY_OP(|=,bitwise_or_assign)
	BINARY_OP(&=,bitwise_and_assign)
	BINARY_OP(^=,bitwise_xor_assign)

	//other operators
	BINARY_OP(->*,member_pointer)
	template<typename Left,typename Right>
	binary_operator::comma<Left,Right> operator ,(Left &&left,Right &&right){
		return { std::forward<Left>(left),std::forward<Right>(right) };
	}

} //namespace operators
} //namespace ET
} //namespace panlib

#undef UNARY_OP
#undef BINARY_OP

#endif

