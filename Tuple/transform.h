#ifndef PANLIB_TUPLE_TRANSFORM
#define PANLIB_TUPLE_TRANSFORM

#include <utility>
#include <tuple>

#include "tuple.h"
#include "unpack_tuple.h"

namespace panlib{
namespace tuple{
namespace detail{
	using std::get;

	template<typename F,typename ...Args>
	auto transform_impl(F func,Args &&...args)
	->tuple<decltype(func(std::forward<Args>(args)))...>{
		return std::tuple<decltype(func(std::forward<Args>(args)))...>(func(std::forward<Args>(args))...);
	}
	template<typename Tuple,typename F,std::size_t ...Indices>
	auto transform_unpack(Tuple &&tuple,F func,index_tuple<Indices...>)
	->decltype(transform_impl(func,get<Indices>(tuple)...)){
		return transform_impl(func,get<Indices>(tuple)...);
	}
} //namespace detail

template<typename Tuple,typename F>
auto transform(Tuple &&tuple,F func)
->decltype(detail::transform_unpack(std::forward<Tuple>(tuple),func,unpack_tuple<Tuple>::index_tuple())){
	return detail::transform_unpack(std::forward<Tuple>(tuple),func,unpack_tuple<Tuple>::index_tuple());
}

} //namespace tuple
} //namespace panlib

#endif

