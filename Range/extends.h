#ifndef PANLIB_RANGE_EXTENDS
#define PANLIB_RANGE_EXTENDS

#include "concept.h"

namespace panlib{
namespace range{

template<typename Base,typename Derived>
struct extends : concept::choose_range_concept<Base,extends<Base,Derived>>{
private:
	Base range_base;
	
public
	extends(Base base) : range_base(std::move(base)){
	}

	template<typename D = Derived>
	auto front_()
	->decltype(util::crtp_cast<D>(*this).transform(range_base.front())){
		return util::crtp_cast<D>(*this).transform(range_base.front());
	}
	void pop_front_(){
		range_base.pop_front();
	}

	template<typename D = Derived>
	auto back_()
	->decltype(util::crtp_cast<D>(*this).transform(range_base.back())){
		return util::crtp_cast<D>(*this).transform(range_base.back());
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

