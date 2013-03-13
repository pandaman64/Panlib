#ifndef PANLIB_UTILITY_TUPLE_UTIL
#define PANLIB_UTILITY_TUPLE_UTIL

#include <utility>
#include <tuple>
#include <type_traits>

#include "index_tuple.h"
#include "unpack_tuple.h"

namespace panlib{
namespace tuple{

namespace detail{
	template<typename T>
	using rem_ref = typename std::remove_reference<T>::type;

	template<typename F,typename Acc>
	rem_ref<Acc> fold_impl(F,Acc &&acc){
		return acc;
	}
	template<typename F,typename Acc,typename Head,typename ...Tail>
	rem_ref<Acc> fold_impl(F func,Acc &&acc,Head &&head,Tail &&...tail){
		return fold_impl(func,func(std::forward<Acc>(acc),std::forward<Head>(head)),std::forward<Tail>(tail)...);
	}
	template<typename Tuple,typename Acc,typename F,std::size_t ...Indices>
	rem_ref<Acc> fold_unpack(F func,Acc &&acc,Tuple &&tuple,index_tuple<Indices...>){
		return fold_impl(func,std::forward<Acc>(acc),std::get<Indices>(tuple)...);	
	}

	struct _or{
		template<typename T,typename U>
		bool operator ()(T &&lhs,U &&rhs){
			return lhs || rhs;
		}
	};

	struct _and{
		template<typename T,typename U>
		bool operator ()(T &&lhs,U &&rhs){
			return lhs && rhs;
		}
	};
} //namespace detail

template<typename F,typename Acc,typename Tuple>
typename std::remove_reference<Acc>::type fold(F f,Acc &&acc,Tuple &&tuple){
	return detail::fold_unpack(f,acc,tuple,unpack_tuple<Tuple>::index_tuple());
}

template<typename Tuple>
bool any(Tuple &&tuple){
	return fold(detail::_or(),false,std::forward<Tuple>(tuple));
}

template<typename Tuple>
bool all(Tuple &&tuple){
	return fold(detail::_and(),true,std::forward<Tuple>(tuple));
}

} //namespace tuple
} //namespace panlib

#endif

