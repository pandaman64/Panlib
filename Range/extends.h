#ifndef PANLIB_RANGE_EXTENDS
#define PANLIB_RANGE_EXTENDS

#include "range_value_type.h"
#include "concept.h"

namespace panlib{
namespace range{

template<typename Base,typename Derived>
struct extends : concept::choose_range_concept<Base,Derived>{
	using base_type = concept::choose_range_concept<Base,Derived>;
protected:
	Base range_base;
	
public:
	using value_type = typename std::remove_reference<typename range_value_type<typename std::remove_reference<Base>::type>::type>::type;

	extends(Base base) : range_base(std::move(base)){
	}

	auto front_()
	->decltype(range_base.front()){
		return range_base.front();
	}
	void pop_front_(){
		range_base.pop_front();
	}

	auto back_()
	->decltype(range_base.front()){
		return range_base.front();
	}
	void pop_back_(){
		range_base.pop_back();
	}

	bool empty_() const{
		return range_base.empty();
	}
};

} //namespace range
} //namespace panlib

#endif

