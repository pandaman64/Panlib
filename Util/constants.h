#ifndef PANLIB_UTIL_CONSTANTS
#define PANLIB_UTIL_CONSTANTS

#include <type_traits>

namespace panlib{
namespace util{
	using true_ = std::integral_constant<bool,true>;
	using false_ = std::integral_constant<bool,false>;

	template<typename Head,typename ...Tail>
	struct and_ : std::integral_constant<bool,Head{} && and_<Tail...>{}>{
	};
	template<typename Head>
	struct and_<Head> : Head{
	};
	template<typename Head,typename ...Tail>
	struct or_ : std::integral_constant<bool,Head{} || and_<Tail...>{}>{
	};
	template<typename Head>
	struct or_<Head> : Head{
	};
} //namespace util
} //namespace panlib

#endif

