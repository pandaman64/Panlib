#ifndef PANLIB_TUPLE_UNPACK_TUPLE
#define PANLIB_TUPLE_UNPACK_TUPLE

#include <tuple>
#include "index_tuple.h"

namespace panlib{
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

} //namespace tuple
} //namespace panlib

#endif

