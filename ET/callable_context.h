#ifndef PANLIB_ET_CALLABLE_CONTEXT
#define PANLIB_ET_CALLABLE_CONTEXT

#include <type_traits>

#include "evaluate.h"
#include "default_context.h"
#include "tag.h"

namespace panlib{
namespace ET{

namespace detail{
	template<typename Context,typename Expr,
	typename Check = decltype(std::declval<Context>()(std::declval<typename std::remove_reference<Expr>::type::tag>(),std::declval<Expr>(),std::declval<Context&>()))>
	std::integral_constant<bool,true> check_callable(int);
	template<typename Context,typename Expr>
	std::integral_constant<bool,false> check_callable(...);

	template<bool b,typename True,typename False>
	struct if_ : True{};
	template<typename True,typename False>
	struct if_<false,True,False> : False{};

	template<typename Expr,typename Tag,typename Context>
	struct callable_eval{
		auto operator ()(Expr &&expr,Context &ctx)
		->decltype(ctx(Tag{},expr,ctx)){
			return ctx(Tag{},expr,ctx);
		}
	};
} //namespace detail

template<typename Context,typename Expr>
struct is_callable : decltype(detail::check_callable<Context,Expr>(0)){
};

template<typename Context,typename DefaultContext = default_context>
struct callable_context{
	template<typename Expr>
	struct eval : detail::if_<is_callable<Context,Expr>{},detail::callable_eval<Expr,typename std::remove_reference<Expr>::type::tag,Context>,typename DefaultContext::template eval<Expr,Context>>{
	};

	Context &as_context(){
		return static_cast<Context&>(*this);
	}
	Context const& as_context() const{
		return static_cast<Context const&>(*this);
	}
};

} //namespace ET
} //namespace panlib

#endif

