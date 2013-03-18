#ifndef PANLIB_ET_NULL_CONTEXT
#define PANLIB_ET_NULL_CONTEXT

#include "../Tuple/for_each.h"
#include "is_expr.h"

namespace panlib{
namespace ET{

struct null_context{
	template<typename ThisContext>
	struct eval_each{
		ThisContext &ctx;

		eval_each(ThisContext &c) : ctx(c){}

		template<typename Expr>
		void operator ()(Expr const& expr){
			evaluate(expr,ctx);
		}
	};

	template<typename Expr,typename ThisContext = null_context>
	struct eval{
		void operator ()(Expr const& expr,ThisContext const& ctx){
			tuple::for_each(expr.as_tuple(),eval_each<ThisContext>(ctx));
		}
	};
};

} //namespace ET
} //namespace panlib

#endif

