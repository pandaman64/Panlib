#ifndef PANLIB_ET_EVALUATE
#define PANLIB_ET_EVALUATE

#include <type_traits>
#include <utility>

#include "is_expr.h"

namespace panlib{
namespace ET{

namespace detail{

	template<typename T>
	using rem_ref = typename std::remove_reference<T>::type;

	//if Expression Object
	template<typename Expr,typename Context,typename enable_if_expr<Expr>::type* = nullptr>
	auto evaluate(Expr &&expr,Context &context,int)
	->decltype(typename Context::template eval<Expr>()(std::forward<Expr>(expr),context)){
		return typename Context::template eval<Expr>()(std::forward<Expr>(expr),context);
	}
	//if not Expression Object
	template<typename Expr,typename Context,typename disable_if_expr<Expr>::type* = nullptr>
	Expr evaluate(Expr &&expr,Context &context,long){
		return std::forward<Expr>(expr);
	}
} //namespace detail

template<typename Expr,typename Context>
auto evaluate(Expr &&expr,Context &&context)
->decltype(detail::evaluate(std::forward<Expr>(expr),context,0)){
	return detail::evaluate(std::forward<Expr>(expr),context,0);
}

} //namespace ET
} //namespace panlib

#endif

