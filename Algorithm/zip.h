#ifndef PANLIB_ALGORITHM_ZIP
#define PANLIB_ALGORITHM_ZIP

#include <type_traits>
#include <utility>
#include <tuple>

#include "index_tuple.h"
#include "tuple_util.h"

namespace panlib{
namespace algorithm{

template<typename ...Ranges>
struct Zip{
private:
	typedef typename utility::make_index_tuple<0,sizeof...(Ranges) - 1>::type indices_type;

	std::tuple<Ranges...> ranges;

	struct pop_front_{
		template<typename T>
		void operator ()(T &&range) const{
			range.pop_front();
		}
	};
	struct front_{
		template<typename T>
		auto operator ()(T &&range) const
		->decltype(range.front()){
			return range.front();
		}
	};
	struct empty_{
		template<typename T>
		bool operator ()(T &&range) const{
			return range.empty();
		}
	};

public:
	Zip(Ranges ...r) : ranges(std::move(r)...){
	}

	void pop_front(){
		utility::tuple::for_each(ranges,pop_front_());
	}

	auto front()
	->decltype(utility::tuple::transform(ranges,front_())){
		return utility::tuple::transform(ranges,front_());
	}

	bool empty() const{
		return utility::tuple::any(utility::tuple::transform(ranges,empty_()));
	}
};

} //namespace alogrithm
} //namespace panlib

#endif
