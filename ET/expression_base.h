#ifndef PANLIB_ET_EXPRESSION_BASE
#define PANLIB_ET_EXPRESSION_BASE

#include <type_traits>
#include <tuple>
#include <cstddef>

#include "subscription.h"
#include "function_call.h"

namespace panlib{
namespace ET{
	template<typename Expr>
	struct terminal_type{
		typedef Expr type;
	};

	struct expression_root{};
	template<typename Derived>
	struct expression_base : expression_root{
		using term = typename terminal_type<Derived>::type;
		using reference = term&;
		using const_reference = term const&;

		reference as_term(){
			return static_cast<term&>(*this);
		}
		const_reference as_term() const{
			return static_cast<term const&>(*this);
		}
		char const* name() const{
			return as_term().expr_name;
		}

		constexpr expression_base(){}
		constexpr expression_base(expression_base const&){}
		constexpr expression_base(expression_base &&){}

		//operators
		template<typename T>
		subscription_operator::subscription<reference,T> operator [](T &&expr){
				return { this->as_term(),std::forward<T>(expr) };
		}
		template<typename T>
		subscription_operator::subscription<const_reference,T> operator [](T &&expr) const{
				return { this->as_term(),std::forward<T>(expr) };
		}

		template<typename ...Args>
		function_call::function<reference,Args...> operator ()(Args &&...args){
				return { this->as_term(),std::forward<Args>(args)... };
		}
		template<typename ...Args>
		function_call::function<const_reference,Args...> operator ()(Args &&...args) const{
				return { this->as_term(),std::forward<Args>(args)... };
		}
	};
	template<typename Derived>
	struct terminal_type<expression_base<Derived>>{
		typedef typename terminal_type<Derived>::type type;
	};

	template<std::size_t N,typename Expr>
	struct expression_element{
		typedef typename std::tuple_element<N,typename Expr::tuple_type>::type type;	
	};
	template<std::size_t N,typename Expr>
	auto get(expression_base<Expr> &&expr)
	->decltype(std::get<N>(expr.as_term().as_tuple())){
		return std::get<N>(expr.as_term().as_tuple());
	}
	template<std::size_t N,typename Expr>
	auto get(expression_base<Expr> &expr)
	->decltype(std::get<N>(expr.as_term().as_tuple())){
		return std::get<N>(expr.as_term().as_tuple());
	}
	template<std::size_t N,typename Expr>
	auto get(expression_base<Expr> const& expr)
	->decltype(std::get<N>(expr.as_term().as_tuple())){
		return std::get<N>(expr.as_term().as_tuple());
	}

	//accessor
	template<typename Expr>
	auto value(Expr &&expr)
	->decltype(get<0>(std::forward<Expr>(expr))){
		return get<0>(std::forward<Expr>(expr));
	}
	template<typename Expr>
	auto left(Expr &&expr)
	->decltype(get<0>(std::forward<Expr>(expr))){
		return get<0>(std::forward<Expr>(expr));
	}
	template<typename Expr>
	auto right(Expr &&expr)
	->decltype(get<1>(std::forward<Expr>(expr))){
		return get<1>(std::forward<Expr>(expr));
	}
} //namespace ET
} //namespace panlib

#endif

