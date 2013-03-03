#ifndef PANLIB_UTILITY_TUPLE_UTIL
#define PANLIB_UTILITY_TUPLE_UTIL

#include <utility>
#include <tuple>
#include <iosfwd>

#include "index_tuple.h"

namespace panlib{
namespace utility{
namespace tuple{

template<typename Tuple>
struct unpack_tuple{
	typedef typename make_index_tuple<0,std::tuple_size<Tuple>::value - 1>::type type;

	static type index_tuple(){
		return {};
	}
};
template<typename T>
struct unpack_tuple<T&> : unpack_tuple<T>{
};
template<typename T>
struct unpack_tuple<T&&> : unpack_tuple<T>{
};

namespace detail{
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
		for_each_impl(func,std::get<Indices>(tuple)...);
	}

	template<typename F,typename ...Args>
	auto transform_impl(F func,Args &&...args)
	->std::tuple<decltype(func(std::forward<Args>(args)))...>{
		return std::tuple<decltype(func(std::forward<Args>(args)))...>(func(std::forward<Args>(args))...);
	}
	template<typename Tuple,typename F,std::size_t ...Indices>
	auto transform_unpack(Tuple &&tuple,F func,index_tuple<Indices...>)
	->decltype(transform_impl(func,std::get<Indices>(tuple)...)){
		return transform_impl(func,std::get<Indices>(tuple)...);
	}

	bool any_impl(){
		return false;
	}
	template<typename ...Bool>
	bool any_impl(bool head,Bool &&...tail){
		return head || any_impl(tail...);
	}
	template<typename Tuple,std::size_t ...Indices>
	bool any_unpack(Tuple &&tuple,index_tuple<Indices...>){
		return any_impl(std::get<Indices>(tuple)...);
	}

	bool all_impl(){
		return true;
	}
	template<typename ...Bool>
	bool all_impl(bool head,Bool &&...tail){
		return head && all_impl(tail...);
	}
	template<typename Tuple,std::size_t ...Indices>
	bool all_unpack(Tuple &&tuple,index_tuple<Indices...>){
		return all_impl(std::get<Indices>(tuple)...);
	}

	template<typename Stream,typename Head>
	void print_tuple_impl(Stream &os,Head &&head){
		os << head << ')';
	}
	template<typename Stream,typename Head,typename ...Tail>
	void print_tuple_impl(Stream &os,Head &&head,Tail &&...tail){
		os << head << ',';
		print_tuple_impl(os,tail...);
	}
	template<typename Stream,typename Tuple,std::size_t ...Indices>
	void print_tuple_unpack(Stream &os,Tuple &&tuple,panlib::utility::index_tuple<Indices...>){
		os << '(';
		print_tuple_impl(os,std::get<Indices>(tuple)...);
	}
} //namespace detail

template<typename Tuple,typename F>
void for_each(Tuple &&tuple,F func){
	detail::for_each_unpack(std::forward<Tuple>(tuple),func,unpack_tuple<Tuple>::index_tuple());
}

template<typename Tuple,typename F>
auto transform(Tuple &&tuple,F func)
->decltype(detail::transform_unpack(std::forward<Tuple>(tuple),func,unpack_tuple<Tuple>::index_tuple())){
	return detail::transform_unpack(std::forward<Tuple>(tuple),func,unpack_tuple<Tuple>::index_tuple());
}

template<typename Tuple>
bool any(Tuple &&tuple){
	return detail::any_unpack(std::forward<Tuple>(tuple),unpack_tuple<Tuple>::index_tuple());
}

template<typename Tuple>
bool all(Tuple &&tuple){
	return detail::all_unpack(std::forward<Tuple>(tuple),unpack_tuple<Tuple>::index_tuple());
}


template<typename Stream,typename Tuple>
void print_tuple(Stream &os,Tuple &&tuple){
	detail::print_tuple_unpack(os,tuple,panlib::utility::tuple::unpack_tuple<Tuple>::index_tuple());
}

} //namespace tuple
} //namespace utility
} //namespace panlib

template<typename CharT,typename ...Args>
std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os,std::tuple<Args...> &&tuple){
	panlib::utility::tuple::print_tuple(os,tuple);
	return os;
}

#endif
