#ifndef PANLIB_RANGE_CONCEPT
#define PANLIB_RANGE_CONCEPT

#include <utility>

#include "../Util/constants.h"
#include "../Util/crtp_cast.h"

namespace panlib{
namespace range{
namespace concept{

namespace detail{
	using util::true_;
	using util::false_;
	using util::and_;
	using util::or_;

	template<typename Range,decltype(&Range::front) = &Range::front,decltype(&Range::pop_front) = &Range::pop_front>
	true_ check_front_operation(int);
	template<typename Range>
	false_ check_front_operation(...);

	template<typename Range,decltype(&Range::back) = &Range::back,decltype(&Range::pop_back) = &Range::pop_back>
	true_ check_back_operation(int);
	template<typename Range>
	false_ check_back_operation(...);

	template<typename Range,decltype(&Range::at) = &Range::at>
	true_ check_at_operation(int);
	template<typename Range>
	false_ check_at_operation(...);
} //namespace detail

template<typename Range>
using is_input_range = decltype(detail::check_front_operation<typename std::remove_reference<Range>::type>(0));
template<typename Range>
using is_forward_range = is_input_range<Range>;
template<typename Range>
using is_bidirectional_range = detail::and_<is_forward_range<Range>,decltype(detail::check_back_operation<typename std::remove_reference<Range>::type>(0))>;
template<typename Range>
using is_random_access_range = detail::and_<is_bidirectional_range<Range>,decltype(detail::check_at_operation<typename std::remove_reference<Range>::type>(0))>;

template<typename Derived>
struct forward_range_concept{	
	template<typename D = Derived>
	auto front()
	->decltype(util::crtp_cast<D>(*this).front_()){
		return util::crtp_cast<D>(*this).front_();
	}
	void pop_front(){
		return util::crtp_cast<Derived>(*this).pop_front_();
	}

	bool empty() const{
		return util::crtp_cast<Derived>(*this).empty_();
	}
};
template<typename Derived>
struct bidirectional_range_concept : forward_range_concept<Derived>{
	template<typename D = Derived>
	auto back()
	->decltype(util::crtp_cast<D>(*this).back_()){
		return util::crtp_cast<D>(*this).back_();
	}
	void pop_back(){
		return util::crtp_cast<Derived>(*this).pop_back_();
	}
};
template<typename Derived>
struct random_access_range_concept : bidirectional_range_concept<Derived>{
	template<typename D = Derived>
	auto at(std::size_t index)
	->decltype(util::crtp_cast<D>(*this).at_(index)){
		return util::crtp_cast<D>(*this).at_(index);
	}
};

template<typename Base,typename Derived = Base,
	bool is_forward = is_forward_range<Base>{},
	bool is_bidirectional = is_bidirectional_range<Base>{},
	bool is_random_access = is_random_access_range<Base>{}
>
struct choose_range_concept;
template<typename Base,typename Derived>
struct choose_range_concept<Base,Derived,true,false,false> : forward_range_concept<Derived>{
	using base = forward_range_concept<Derived>;
};
template<typename Base,typename Derived>
struct choose_range_concept<Base,Derived,true,true,false> : bidirectional_range_concept<Derived>{
	using base = bidirectional_range_concept<Derived>;
};
template<typename Base,typename Derived>
struct choose_range_concept<Base,Derived,true,true,true> : random_access_range_concept<Derived>{
	using base = random_access_range_concept<Derived>;
};

} //namespace concept
} //namespace range
} //namespace panlib

#endif

