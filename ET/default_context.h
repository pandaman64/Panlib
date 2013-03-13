#ifndef PANLIB_ET_DEFAULT_CONTEXT
#define PANLIB_ET_DEFAULT_CONTEXT

#include "evaluate.h"
#include "unary_operator.h"
#include "binary_operator.h"
#include "subscription.h"
#include "function_call.h"

#define UNARY_OP(name,op)\
template<typename T>\
struct default_context::eval<unary_operator::name<T>>{\
	auto operator ()(unary_operator::name<T> const& expr,default_context const& ctx)\
	->decltype(op evaluate(value(expr),ctx)){\
		return op evaluate(value(expr),ctx);\
	}\
}
#define UNARY_OP_POST(name,op)\
template<typename T>\
struct default_context::eval<unary_operator::name<T>>{\
	auto operator ()(unary_operator::name<T> const& expr,default_context const& ctx)\
	->decltype(evaluate(value(expr),ctx) op){\
		return evaluate(value(expr),ctx) op;\
	}\
}
#define BINARY_OP(name,op)\
template<typename Left,typename Right>\
struct default_context::eval<binary_operator::name<Left,Right>>{\
	auto operator ()(binary_operator::name<Left,Right> const& expr,default_context const& ctx)\
	->decltype(evaluate(left(expr),ctx) op evaluate(right(expr),ctx)){\
		return evaluate(left(expr),ctx) op evaluate(right(expr),ctx);\
	}\
}

namespace panlib{
namespace ET{

struct default_context{
	template<typename Expr>
	struct eval;
};
UNARY_OP(plus,+); //unary +
UNARY_OP(negate,-); //unary -
UNARY_OP(dereference,*); //unary *
UNARY_OP(complement,~); //unary ~
UNARY_OP(address_of,&); //unary &
UNARY_OP(logical_not,!); //unary !
UNARY_OP(prefix_increment,++); //unary pre ++
UNARY_OP(prefix_decrement,--); //unary pre --
UNARY_OP_POST(postfix_increment,++); //unary post ++
UNARY_OP_POST(postfix_decrement,--); //unary post --

//numeric operators
BINARY_OP(plus,+); //binary +
BINARY_OP(minus,-); //binary -
BINARY_OP(multiple,*); //binary *
BINARY_OP(divide,/); //binary / 
BINARY_OP(module,%); //binary %
BINARY_OP(left_shift,<<); //binary <<
BINARY_OP(right_shift,>>); //binary >>

//compare operators
BINARY_OP(less,<); //binary <
BINARY_OP(greater,>); //binary >
BINARY_OP(less_equal,<=); //binary <=
BINARY_OP(greater_equal,>=); //binary >=
BINARY_OP(equal_to,==); //binary ==
BINARY_OP(not_equal_to,!=); //binary !=

//logical operators
BINARY_OP(logical_or,||); //binary ||
BINARY_OP(logical_and,&&); //binary &&
BINARY_OP(bitwise_or,|); //binary |
BINARY_OP(bitwise_and,&); //binary &
BINARY_OP(bitwise_xor,^); //binary ^

//assign operators
BINARY_OP(assign,=); //binary =
BINARY_OP(plus_assign,+=); //binary +=
BINARY_OP(minus_assign,-=); //binary -=
BINARY_OP(multiple_assign,*=); //binary *=
BINARY_OP(divide_assign,/=); //binary /=
BINARY_OP(module_assign,%=); //binary %=
BINARY_OP(left_shift_assign,<<=); //binary <<=
BINARY_OP(right_shift_assign,>>=); //binary >>=
BINARY_OP(bitwise_or_assign,|=); //binary |=
BINARY_OP(bitwise_and_assign,&=); //binary &=
BINARY_OP(bitwise_xor_assign,^=); //binary ^=

//other operators
BINARY_OP(member_pointer,->*); //binary ->*

template<typename Left,typename Right>
struct default_context::eval<subscription_operator::subscription<Left,Right>>{
	auto operator ()(subscription_operator::subscription<Left,Right> const& expr,default_context const& ctx)
	->decltype(evaluate(left(expr),ctx)[evaluate(right(expr),ctx)]){
		return evaluate(left(expr),ctx)[evaluate(right(expr),ctx)];
	}
};
template<typename Callee,typename ...Args>
struct default_context::eval<function_call::function<Callee,Args...>>{
	using Expr = function_call::function<Callee,Args...>;

	template<typename C,typename ...As>
	static auto call(C &&callee,As &&...args)
	->decltype(std::forward<C>(callee)(std::forward<As>(args)...)){
		return std::forward<C>(callee)(std::forward<As>(args)...);
	}

	template<typename ...As,std::size_t ...Indices>
	static auto unpack(std::tuple<As...> as,index_tuple<Indices...>,default_context const& ctx)
	->decltype(call(evaluate(std::get<Indices>(as),ctx)...)){
		return call(evaluate(std::get<Indices>(as),ctx)...);
	}

	auto operator ()(Expr const& expr,default_context const& ctx)
	->decltype(unpack(expr.as_tuple(),tuple::unpack_tuple<typename Expr::tuple_type>::index_tuple(),ctx)){
		return unpack(expr.as_tuple(),tuple::unpack_tuple<typename Expr::tuple_type>::index_tuple(),ctx);
	}
};

template<typename Left,typename Right>
struct default_context::eval<binary_operator::comma<Left,Right>>{
	auto operator ()(binary_operator::comma<Left,Right> const& expr,default_context const& ctx)
	->decltype(evaluate(left(expr),ctx),evaluate(right(expr),ctx)){
		return evaluate(left(expr),ctx),evaluate(right(expr),ctx);
	}
};

template<typename T>
struct default_context::eval<terminal<T>>{
	T operator ()(terminal<T> const& expr,default_context const& ctx){
		return evaluate(value(expr),ctx);
	}
};

} //namespace ET
} //namespace panlib
#endif
