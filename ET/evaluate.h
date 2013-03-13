#ifndef PANLIB_ET_EVALUATE
#define PANLIB_ET_EVALUATE

#include <type_traits>
#include "expression_base.h"

namespace panlib{
namespace ET{
namespace detail{
	template<typename Expr,typename Context,typename std::enable_if<std::is_base_of<expression_root,Expr>{}>::type* = nullptr>
	auto evaluate(Expr const& expr,Context const& context)
	->decltype(typename Context::template eval<Expr>()(expr,context)){
		return typename Context::template eval<Expr>()(expr,context);
	}
	template<typename Expr,typename Context,typename std::enable_if<!std::is_base_of<expression_root,Expr>{}>::type* = nullptr>
	Expr evaluate(Expr const& expr,Context const&){
		return expr;
	}
} //namespace detail

template<typename Expr,typename Context>
auto evaluate(Expr const& expr,Context const& context)
->decltype(detail::evaluate(expr,context)){
	return detail::evaluate(expr,context);
}

} //namespace ET
} //namespace panlib

#endif

