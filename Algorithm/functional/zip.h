#ifndef PANLIB_ALGORITHM_ZIP_FUNCTIONAL
#define PANLIB_ALGORITHM_ZIP_FUNCTIONAL

#include "../zip.h"

namespace panlib{
namespace algorithm{

template<typename ...Ranges>
Zip<Ranges...> zip(Ranges ...ranges){
	return { std::move(ranges)... };
}

} //namespace alogrithm
} //namespace panlib

#endif
