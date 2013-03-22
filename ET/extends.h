#ifndef PANLIB_ET_EXTENDS
#define PANLIB_ET_EXTENDS

#include "expression_base.h"

#include <utility>

namespace panlib{
namespace ET{

	template<typename Expr,typename Derived,typename Domain>
	struct extends{
		using term = Derived;
		using reference = term&;
		using const_reference = term const&;

		Expr expression;

		template<typename Exp>
		extends(Exp &&expr) : expression(std::forward<Exp>(expr)){
		}
		extends(extends const& other) : expression(other.expression){
		}
		extends(extends &&other) : expression(std::move(other.expression)){
		}

		reference as_term(){
			return static_cast<term&>(*this);
		}
		const_reference as_term() const{
			return static_cast<term&>(*this);
		}
		char const* name() const{
			return as_term().expr_name;
		}
	};

	template<typename Expr,typename Derived,typename Domain>
	struct terminal_type<extends<Expr,Derived,Domain>>{
		typedef Derived type;
	};
} //namespace ET
} //namespace panlib

#endif

