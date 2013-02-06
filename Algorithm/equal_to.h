#ifndef PANLIB_ALGORITHM_EQUAL_TO
#define PANLIB_ALGORITHM_EQUAL_TO

namespace panlib{
namespace algorithm{

struct equal_to{
	template<typename T,typename U>
	bool operator ()(T &&lhs,U &&rhs) const{
		return lhs == rhs;
	}
};

} //namespace algorithm
} //namespace panlib

#endif
