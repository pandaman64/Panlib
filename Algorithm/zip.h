#ifndef PANLIB_ALGORITHM_ZIP
#define PANLIB_ALGORITHM_ZIP

#include <type_traits>
#include <tuple>

#include "index_tuple.h"

namespace panlib{
namespace algorithm{

template<typename ...Ranges>
struct Zip{
private:
	typedef typename utility::make_index_tuple<0,sizeof...(Ranges)>::type indices_type;

	std::tuple<Ranges...> ranges;

	template<std::size_t ...Indices>
	void pop_front_impl(utility::index_tuple<Indices...>){
		std::get<Indices>(ranges).pop_front()...;
	}

	template<std::size_t ...Indices>
	auto front_impl(utility::index_tuple<Indices...>)
	->decltype(std::tuple<decltype(std::get<Indices>())...>(std::get<Indices>(ranges).front()...)){
		return std::tuple<decltype(std::get<Indices>())...>(std::get<Indices>(ranges).front()...);
	}

	template<typename ...Args>
	bool _all(bool head,Args&& ...tail) const{
		return head && _all(tail...);
	}
	bool _all(bool head,bool tail) const{
		return head && tail;
	}

	template<std::size_t ...Indices>
	bool empty_impl(utility::index_tuple<Indices...>) const{
		return _all(std::get<Indices>(ranges).empty()...);
	}

public:
	Zip(Ranges ...r) : ranges(std::move(r)...){
	}

	void pop_front(){
		pop_front_impl();
	}

	auto front()
	->decltype(front_impl()){
		return front_impl();
	}

	bool empty() const{
		return empty_impl();
	}
};

} //namespace alogrithm
} //namespace panlib

#endif
