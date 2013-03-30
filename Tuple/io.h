#ifndef PANLIB_TUPLE_IO
#define PANLIB_TUPLE_IO

#include <iosfwd>

#include "unpack_tuple.h"
#include "tuple.h"

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
		using std::get;
		os << '(';
		print_tuple_impl(os,get<Indices>(tuple)...);
	}
} //namespace detail

template<typename Stream,typename Tuple>
void print_tuple(Stream &os,Tuple &&tuple){
	detail::print_tuple_unpack(os,tuple,unpack_tuple<Tuple>::index_tuple());
}

template<typename CharT,typename Traits,typename ...Args>
std::basic_ostream<CharT,Traits>& operator <<(std::basic_ostream<CharT,Traits> &os,tuple<Args...> tuple){
	panlib::tuple::print_tuple(os,tuple);
	return os;
}

} //namespace tuple
} //namespace panlib

#endif

