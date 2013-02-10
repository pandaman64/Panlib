#ifndef PANLIB_ALGORITHM_LESS_THAN
#define PANLIB_ALGORITHM_LESS_THAN

namespace panlib{
namespace algorithm{

struct less_than{
	template<typename T,typename U>
	bool operator ()(T &&lhs,U &&rhs) const{
		return lhs < rhs;
	}
};

} //namespace algorithm
} //namespace panlib

#endif
