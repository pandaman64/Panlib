#ifndef PANLIB_TUPLE_IO
#define PANLIB_TUPLE_IO

#include <tuple>
#include "unpack_tuple.h"

namespace panlib{
namespace tuple{

namespace detail{
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
	void print_tuple_unpack(Stream &os,Tuple &&tuple,panlib::index_tuple<Indices...>){
		os << '(';
		print_tuple_impl(os,std::get<Indices>(tuple)...);
	}
} //namespace detail

template<typename Stream,typename Tuple>
void print_tuple(Stream &os,Tuple &&tuple){
	detail::print_tuple_unpack(os,tuple,unpack_tuple<Tuple>::index_tuple());
}

} //namespace tuple
} //namespace panlib

template<typename CharT,typename ...Args>
std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os,std::tuple<Args...> &&tuple){
	panlib::tuple::print_tuple(os,tuple);
	return os;
}

#endif

