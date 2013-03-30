#ifndef PANLIB_ALGORITHM_MAP
#define PANLIB_ALGORTIHM_MAP

#include <utility>
#include <type_traits>

#include "../Range/extends.h"

namespace panlib{
namespace algorithm{

template<typename Range,typename Pred>
struct Map : range::extends<Range,Map<Range,Pred>>{
	using base = panlib::range::extends<Range,Map>;

private:
	Pred pred;

public:
	Map(Range r,Pred p) : base(std::move(r)),pred(p){
	}

	auto front_()
	->decltype(pred(this->base::front_())){
		return pred(base::front_());
	}
	auto back_()
	->decltype(pred(this->base::back_())){
		return pred(base::back_());
	}
};

} //namespace algorithm
} //namespace panlib

#endif
