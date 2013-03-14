#ifndef PANLIB_ET_CALLABLE_CONTEXT
#define PANLIB_ET_CALLABLE_CONTEXT

#include <type_traits>

#include "evaluate.h"
#include "default_context.h"
#include "tag.h"

template<typename T>
void print_type(T &&v);

#define UNARY_OP(name)\
template<typename Context,typename DefaultContext>\
template<typename T>\
struct callable_context<Context,DefaultContext>::eval<unary_operator::name<T>>{\
	auto operator ()(unary_operator::name<T> const& expr,callable_context<Context,DefaultContext> const& ctx) const\
	->decltype(ctx.call(tag::unary_operator::name(),expr,ctx)){\
		return ctx.call(tag::unary_operator::name(),expr,ctx);\
	}\
}
#define BINARY_OP(name)\
template<typename Context,typename DefaultContext>\
template<typename Left,typename Right>\
struct callable_context<Context,DefaultContext>::eval<binary_operator::name<Left,Right>>{\
	auto operator ()(binary_operator::name<Left,Right> const& expr,callable_context<Context,DefaultContext> const& ctx) const\
	->decltype(ctx.call(tag::binary_operator::name(),expr,ctx)){\
		return ctx.call(tag::binary_operator::name(),expr,ctx);\
	}\
}

namespace panlib{
namespace ET{

namespace detail{
	template<typename Context,typename Expr,
	typename Check = decltype(std::declval<Context>()(std::declval<typename Expr::tag>(),std::declval<Expr>(),std::declval<Context>()))>
	std::integral_constant<bool,true> check_callable(int);
	template<typename Context,typename Expr>
	std::integral_constant<bool,false> check_callable(...);

	template<bool b,typename True,typename False>
	struct if_ : True{};
	template<typename True,typename False>
	struct if_<false,True,False> : False{};

	template<typename Expr>
	struct callable_eval{
		template<typename Context>
		auto operator ()(Expr const& expr,Context const& ctx)
		->decltype(ctx(Expr::tag(),expr,ctx)){
			return ctx(Expr::tag(),expr,ctx);
		}
	};
} //namespace detail

template<typename Context,typename Expr>
struct is_callable : decltype(detail::check_callable<Context,Expr>(0)){
};

template<typename Context,typename DefaultContext = default_context>
struct callable_context{
	template<typename Expr>
	struct eval : detail::if_<is_callable<Context,Expr>{},detail::callable_eval<Expr>,typename DefaultContext::template eval<Expr>>{
	};

	Context &as_context(){
		return static_cast<Context&>(*this);
	}
	Context const& as_context() const{
		return static_cast<Context const&>(*this);
	}
/*
	template<typename Tag,typename Expr,typename Ctx,typename std::enable_if<is_callable<Context,Tag,Expr>{}>::type* = nullptr>
	auto call(Tag tag,Expr const& expr,Ctx const& ctx) const
	->decltype(this->as_context()(tag,expr,ctx)){
		std::cout << "callable\n";
		std::cout << "Ctx is ";
		print_type(ctx);
		std::cout << "tag is ";
		print_type(tag);
		std::cout << "expr is ";
		print_type(expr);
		return this->as_context()(tag,expr,ctx);
	}
	template<typename Tag,typename Expr,typename Ctx,typename std::enable_if<!is_callable<Context,Tag,Expr>{}>::type* = nullptr>
	auto call(Tag tag,Expr const& expr,Ctx const& ctx) const
	->decltype(evaluate(expr,DefaultContext())){
		std::cout << "defalut\n";
		std::cout << "Ctx is ";
		print_type(ctx);
		std::cout << "tag is ";
		print_type(tag);
		std::cout << "expr is ";
		print_type(expr);
		return evaluate(expr,DefaultContext());
	}
	*/
};
/*
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

template<typename Context,typename DefaultContext>
template<typename ...Args>
struct callable_context<Context,DefaultContext>::eval<function_call::function<Args...>>{
	auto operator ()(function_call::function<Args...> const& expr,callable_context<Context,DefaultContext> const& ctx) const
	->decltype(ctx.call(tag::function_call::function(),expr,ctx)){
		return ctx.call(tag::function_call::function(),expr,ctx);
	}
};

template<typename Context,typename DefaultContext>
template<typename T>
struct callable_context<Context,DefaultContext>::eval<terminal<T>>{
	auto operator ()(terminal<T> const& expr,callable_context<Context,DefaultContext> const& ctx) const
	->decltype(ctx.call(tag::terminal(),expr,ctx)){
		return ctx.call(tag::terminal(),expr,ctx);
	}
};
*/
} //namespace ET
} //namespace panlib

#undef UNARY_OP
#undef BINARY_OP

#endif

