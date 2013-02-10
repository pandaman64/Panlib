#ifndef PANLIB_ALGORITHM_MORE_THAN
#define PANLIB_ALGORITHM_MORE_THAN

namespace panlib{
namespace algorithm{

struct more_than{
	template<typename T,typename U>
	bool operator ()(T &&lhs,U &&rhs) const{
		return lhs > rhs;
	}
};

} //namespace algorithm
} //namespace panlib

#endif
