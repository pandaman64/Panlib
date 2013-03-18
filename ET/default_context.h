#ifndef PANLIB_ET_DEFAULT_CONTEXT
#define PANLIB_ET_DEFAULT_CONTEXT

#include "../Tuple/index_tuple.h"
#include "../Tuple/unpack_tuple.h"

#include "evaluate.h"
#include "unary_operator.h"
#include "binary_operator.h"
#include "subscription.h"
#include "function_call.h"
#include "terminal.h"

#define UNARY_OP(name,op)\
template<typename Expr,typename Context>\
struct default_context_eval<Expr,Context,tag::unary_operator::name>{\
	auto operator ()(Expr &&expr,Context &ctx)\
	->decltype(op evaluate(value(std::forward<Expr>(expr)),ctx)){\
		return op evaluate(value(std::forward<Expr>(expr)),ctx);\
	}\
}
#define UNARY_OP_POST(name,op)\
template<typename Expr,typename Context>\
struct default_context_eval<Expr,Context,tag::unary_operator::name>{\
	auto operator ()(Expr &&expr,Context &ctx)\
	->decltype(evaluate(value(std::forward<Expr>(expr)),ctx) op){\
		return evaluate(value(std::forward<Expr>(expr)),ctx) op;\
	}\
}
#define BINARY_OP(name,op)\
template<typename Expr,typename Context>\
struct default_context_eval<Expr,Context,tag::binary_operator::name>{\
	auto operator ()(Expr &&expr,Context &ctx)\
	->decltype(evaluate(left(std::forward<Expr>(expr)),ctx) op evaluate(right(std::forward<Expr>(expr)),ctx)){\
		return evaluate(left(std::forward<Expr>(expr)),ctx) op evaluate(right(std::forward<Expr>(expr)),ctx);\
	}\
}

namespace panlib{
namespace ET{

	struct default_context;

namespace detail{
	template<typename Expr,typename Context,typename Tag = typename std::remove_reference<Expr>::type::tag>
	struct default_context_eval{};

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

	template<typename Expr,typename Context>
	struct default_context_eval<Expr,Context,tag::binary_operator::subscription>{
		auto operator ()(Expr &&expr,Context &ctx)
		->decltype(evaluate(left(std::forward<Expr>(expr)),ctx)[evaluate(right(std::forward<Expr>(expr)),ctx)]){
			return evaluate(left(std::forward<Expr>(expr)),ctx)[evaluate(right(std::forward<Expr>(expr)),ctx)];
		}
	};
	template<typename Expr,typename Context>
	struct default_context_eval<Expr,Context,tag::function_call::function>{
		template<typename C,typename ...As>
		static auto call(C &&callee,As &&...args)
		->decltype(std::forward<C>(callee)(std::forward<As>(args)...)){
			return std::forward<C>(callee)(std::forward<As>(args)...);
		}

		template<typename ...As,std::size_t ...Indices>
		static auto unpack(std::tuple<As...> as,index_tuple<Indices...>,default_context &&ctx)
		->decltype(call(evaluate(std::get<Indices>(as),ctx)...)){
			return call(evaluate(std::get<Indices>(as),ctx)...);
		}

		auto operator ()(Expr &&expr,Context &ctx)
		->decltype(unpack(std::forward<Expr>(expr).as_tuple(),tuple::unpack_tuple<typename Expr::tuple_type>::index_tuple(),ctx)){
			return unpack(std::forward<Expr>(expr).as_tuple(),tuple::unpack_tuple<typename Expr::tuple_type>::index_tuple(),ctx);
		}
	};

	template<typename Expr,typename Context>
	struct default_context_eval<Expr,Context,tag::binary_operator::comma>{
		auto operator ()(Expr &&expr,Context &ctx)
		->decltype(evaluate(left(std::forward<Expr>(expr)),ctx),evaluate(right(std::forward<Expr>(expr)),ctx)){
			return evaluate(left(std::forward<Expr>(expr)),ctx),evaluate(right(std::forward<Expr>(expr)),ctx);
		}
	};

	template<typename Expr,typename Context>
	struct default_context_eval<Expr,Context,tag::terminal>{
		auto operator ()(Expr &&expr,Context &ctx)
		->decltype(value(std::forward<Expr>(expr))){
			return value(std::forward<Expr>(expr));
		}
	};
} //namespace detail

struct default_context{
	template<typename Expr,typename ThisContext = default_context>
	struct eval : detail::default_context_eval<Expr,ThisContext>{
	};
};
#undef UNARY_OP
#undef UNARY_OP_POST
#undef BINARY_OP

} //namespace ET
} //namespace panlib
#endif

