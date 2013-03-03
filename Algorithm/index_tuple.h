#ifndef PANLIB_UTILITY_INDEX_TUPLE
#define PANLIB_UTILITY_INDEX_TUPLE

#include <cstddef>

namespace panlib{
namespace utility{

template<std::size_t...>
struct index_tuple{};

template<std::size_t N,typename Indices>
struct make_index_tuple_impl;
template<std::size_t N,std::size_t ...Indices>
struct make_index_tuple_impl<N,index_tuple<Indices...>>{
	typedef index_tuple<N,Indices...> type;
};

template<std::size_t Beg,std::size_t End>
struct make_index_tuple{
	typedef typename make_index_tuple_impl<Beg,typename make_index_tuple<Beg + 1,End>::type>::type type;
};
template<std::size_t End>
struct make_index_tuple<End,End>{
	typedef index_tuple<End> type;
};

} //namespace utility
} //namepsace panlib

#endif
