#ifndef PANLIB_TUPLE_TUPLE
#define PANLIB_TUPLE_TUPLE

#include <tuple>
#include <utility>

namespace panlib{
namespace tuple{

template<typename ...Args>
struct tuple{
	using base_type = std::tuple<Args...>;
	base_type base;

	constexpr tuple() : base(){
	}
	template<typename ...Types>
	explicit tuple(Types &&...args) : base(std::forward<Types>(args)...){
	}
	tuple(base_type const& b) : base(b){
	}
	tuple(base_type &&b) : base(std::move(b)){
	}
	tuple(tuple const&) = default;
	tuple(tuple &&) = default;
	template<typename ...Types>
	tuple(tuple<Types...> const& other) : base(other.base){
	}
	template<typename ...Types>
	tuple(tuple<Types...> &&other) : base(std::move(other.base)){
	}

	tuple &operator =(tuple const& other){
		tuple tmp = other;
		swap(tmp);
		return *this;
	}
	tuple &operator =(tuple &&other){
		tuple tmp = std::move(other);
		swap(tmp);
		return *this;
	}
	template<typename T>
	tuple &operator =(T &&other){
		base = std::forward<T>(other);
		return *this;
	}

	void swap(tuple &other){
		base.swap(other.base);
	}

	template<std::size_t I>
	friend auto get(tuple &t)
	->decltype(std::get<I>(t.base)){
		return std::get<I>(t.base);
	}
	template<std::size_t I>
	friend auto get(tuple &&t)
	->decltype(std::get<I>(t.base)){
		return std::get<I>(t.base);
	}
	template<std::size_t I>
	friend auto get(tuple const& t)
	->decltype(std::get<I>(t.base)){
		return std::get<I>(t.base);
	}

	template<typename ...Ts,typename ...Us>
	friend bool operator ==(tuple<Ts...> const& lhs,tuple<Us...> const& rhs);
	template<typename ...Ts,typename ...Us>
	friend bool operator !=(tuple<Ts...> const& lhs,tuple<Us...> const& rhs);
	template<typename ...Ts,typename ...Us>
	friend bool operator <(tuple<Ts...> const& lhs,tuple<Us...> const& rhs);
	template<typename ...Ts,typename ...Us>
	friend bool operator >(tuple<Ts...> const& lhs,tuple<Us...> const& rhs);
	template<typename ...Ts,typename ...Us>
	friend bool operator <=(tuple<Ts...> const& lhs,tuple<Us...> const& rhs);
	template<typename ...Ts,typename ...Us>
	friend bool operator >=(tuple<Ts...> const& lhs,tuple<Us...> const& rhs);
};

template<typename ...Ts,typename ...Us>
bool operator ==(tuple<Ts...> const& lhs,tuple<Us...> const& rhs){
	return lhs.base == rhs.base;
}
template<typename ...Ts,typename ...Us>
bool operator !=(tuple<Ts...> const& lhs,tuple<Us...> const& rhs){
	return lhs.base != rhs.base;
}
template<typename ...Ts,typename ...Us>
bool operator <(tuple<Ts...> const& lhs,tuple<Us...> const& rhs){
	return lhs.base < rhs.base;
}
template<typename ...Ts,typename ...Us>
bool operator >(tuple<Ts...> const& lhs,tuple<Us...> const& rhs){
	return lhs.base > rhs.base;
}
template<typename ...Ts,typename ...Us>
bool operator <=(tuple<Ts...> const& lhs,tuple<Us...> const& rhs){
	return lhs.base <= rhs.base;
}
template<typename ...Ts,typename ...Us>
bool operator >=(tuple<Ts...> const& lhs,tuple<Us...> const& rhs){
	return lhs.base >= rhs.base;
}

template<typename ...Args>
void swap(tuple<Args...> &lhs,tuple<Args...> &rhs){
	lhs.swap(rhs);
}

} //namespace tuple
} //namespace panlib

namespace std{
	template<typename ...Args>
	class tuple_size<panlib::tuple::tuple<Args...>> : public tuple_size<typename panlib::tuple::tuple<Args...>::base_type>{
	};

	template<std::size_t I,typename ...Args>
	class tuple_element<I,panlib::tuple::tuple<Args...>> : public tuple_element<I,typename panlib::tuple::tuple<Args...>::base_type>{
	};
}

namespace panlib{
namespace tuple{

template<typename ...Args>
tuple<Args...> make_tuple_impl(std::tuple<Args...> const& base){
	return { base };
}
template<typename ...Args>
tuple<Args...> make_tuple_impl(std::tuple<Args...> &&base){
	return { std::move(base) };
}
template<typename ...Args>
auto make_tuple(Args &&...args)
->decltype(make_tuple_impl(std::make_tuple(std::forward<Args>(args)...))){
	return make_tuple_impl(std::make_tuple(std::forward<Args>(args)...));
}

template<typename ...Args>
tuple<Args&...> tie(Args &...args) noexcept{
	return tuple<Args&...>(args...);
}

template<typename ...Args>
tuple<Args&&...> forward_as_tuple(Args &&...args){
	return tuple<Args&&...>(std::forward<Args>(args)...);
}

template<typename ...Tuples>
auto tuple_cat(Tuples &&...tuples)
->decltype(forward_as_tuple(std::tuple_cat(std::forward<Tuples>(tuples)...))){
	return forward_as_tuple(std::tuple_cat(std::forward<Tuples>(tuples)...));
}

} //namespace tuple
} //namespace panlib

#endif

