#ifndef PANLIB_TUPLE_FOR_EACH
#define PANLIB_TUPLE_FOR_EACH

#include <utility>
#include <tuple>

#include "unpack_tuple.h"

namespace panlib{
namespace tuple{
namespace detail{
	using std::get;

	template<typename F>
	void for_each_impl(F func){
	}
	template<typename F,typename Head,typename ...Tail>
	void for_each_impl(F func,Head &&head,Tail &&...tail){
		func(std::forward<Head>(head));
		for_each_impl(func,std::forward<Tail>(tail)...);
	}
	template<typename Tuple,typename F,std::size_t ...Indices>
	void for_each_unpack(Tuple &&tuple,F func,index_tuple<Indices...>){
		for_each_impl(func,get<Indices>(tuple)...);
	}
} //namespace detail

template<typename Tuple,typename F>
void for_each(Tuple &&tuple,F func){
	detail::for_each_unpack(std::forward<Tuple>(tuple),func,unpack_tuple<Tuple>::index_tuple());
}

} //namespace tuple
} //namespace panlib

#endif

