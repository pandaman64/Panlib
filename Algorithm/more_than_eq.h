#ifndef PANLIB_ALGORITHM_MORE_THAN_EQ
#define PANLIB_ALGORITHM_MORE_THAN_EQ

namespace panlib{
namespace algorithm{

struct more_than_eq{
	template<typename T,typename U>
	bool operator ()(T &&lhs,U &&rhs) const{
		return lhs >= rhs;
	}
};

} //namespace algorithm
} //namespace panlib

#endif
