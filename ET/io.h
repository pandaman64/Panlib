#ifndef PANLIB_ET_IO
#define PANLIB_ET_IO

#include <iostream>
#include <cstddef>
#include <iosfwd>
#include <tuple>

#include "expression_base.h"
#include "../Tuple/for_each.h"
#include "to_string.h"

namespace panlib{
namespace ET{
namespace detail{
	template<std::size_t Level>
	struct print_expr_impl{
		static void print_shift(){
			for(int level = Level;level--;){
				std::cout << "\t";
			}
		}

		template<typename Expr>
		void operator ()(expression_base<Expr> &expr){
			print_shift();
			std::cout << expr.name() << "(\n";
			tuple::for_each(expr.as_term().as_tuple(),print_expr_impl<Level + 1>());
			print_shift();
			std::cout << "\n)";
		}
		template<typename T>
		void operator ()(T &value,typename std::enable_if<!std::is_base_of<expression_root,T>{}>::type* = nullptr){
			print_shift();
			std::cout << value << ",";
		}
	};
} //namespace detail

template<typename Expr>
void print_expr(Expr &&expr){
	std::cout << to_string(expr) << std::endl;
}

} //namespace ET
} //namespace panlib

#endif

