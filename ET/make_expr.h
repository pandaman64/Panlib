#ifndef PANLIB_ET_MAKE_EXPR
#define PANLIB_ET_MAKE_EXPR

namespace panlib{
namespace ET{

	template<template <typename...> class Expr,typename ...Args>
	Expr<Args...> make_expr(Args &&...args){
	}

} //namespace ET
} //namespace panlib

#endif

