#ifndef PANLIB_ET_EVALUATE
#define PANLIB_ET_EVALUATE

#include <type_traits>

#include "is_expr.h"

namespace panlib{
namespace ET{

namespace detail{
	//if Expression Object
	template<typename Expr,typename Context,typename std::enable_if<std::is_base_of<expression_root,Expr>{}>::type* = nullptr>
	auto evaluate(Expr const& expr,Context const& context,int)
	->decltype(typename Context::template eval<Expr const>()(expr,context)){
		return typename Context::template eval<Expr const>()(expr,context);
	}
	//if not Expression Object
	template<typename Expr,typename Context,typename std::enable_if<!std::is_base_of<expression_root,Expr>{}>::type* = nullptr>
	Expr evaluate(Expr const& expr,Context const& context,long){
		return expr;
	}
} //namespace detail

template<typename Expr,typename Context>
auto evaluate(Expr const& expr,Context const& context)
->decltype(detail::evaluate(expr,context,0)){
	return detail::evaluate(expr,context,0);
}

} //namespace ET
} //namespace panlib

#endif

