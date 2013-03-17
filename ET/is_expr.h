#ifndef PANLIB_ET_IS_EXPR
#define PANLIB_ET_IS_EXPR

#include <type_traits>

#include "expression_base.h"

namespace panlib{
namespace ET{

template<typename Expr>
using is_expr = std::is_base_of<expression_root,Expr>;

template<typename Expr>
using enable_if_expr = std::enable_if<is_expr<Expr>{}>;
template<typename Expr>
using disable_if_expr = std::enable_if<!is_expr<Expr>{}>;

} //namespace ET
} //namespace panlib

#endif

