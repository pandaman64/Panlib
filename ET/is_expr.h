#ifndef PANLIB_ET_IS_EXPR
#define PANLIB_ET_IS_EXPR

#include <type_traits>

#include "expression_base.h"
#include "extends.h"

namespace panlib{
namespace ET{

template<typename Expr>
struct is_expr : std::is_base_of<expression_root,Expr>{
};
//Extention is an expression
template<typename Expr,typename Derived,typename Domain>
struct is_expr<extends<Expr,Derived,Domain>> : std::integral_constant<bool,true>{
};

template<typename Expr>
using enable_if_expr = std::enable_if<is_expr<typename std::remove_reference<Expr>::type>{}>;
template<typename Expr>
using disable_if_expr = std::enable_if<!is_expr<typename std::remove_reference<Expr>::type>{}>;

} //namespace ET
} //namespace panlib

#endif

