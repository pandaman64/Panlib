#ifndef PANLIB_ALGORITHM_ZIP
#define PANLIB_ALGORITHM_ZIP

#include <type_traits>
#include <utility>

#include "../Tuple/index_tuple.h"
#include "../Tuple/tuple.h"
#include "../Tuple/fold.h"
#include "../Tuple/for_each.h"
#include "../Tuple/transform.h"

namespace panlib{
namespace algorithm{

template<typename ...Ranges>
struct Zip{
//private:
	panlib::tuple::tuple<Ranges...> ranges;

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
		tuple::for_each(ranges,pop_front_());
	}

	auto front()
	->decltype(tuple::transform(ranges,front_())){
		return tuple::transform(ranges,front_());
	}

	bool empty() const{
		return tuple::any(tuple::transform(ranges,empty_()));
	}
};

} //namespace alogrithm
} //namespace panlib

#endif
