#ifndef PANLIB_UTIL_CRTP_CAST
#define PANLIB_UTIL_CRTP_CAST

namespace panlib{
namespace util{

template<typename Derived,typename Base>
Derived &crtp_cast(Base &base){
	return static_cast<Derived&>(base);
}
template<typename Derived,typename Base>
Derived *crtp_cast(Base *base){
	return static_cast<Derived*>(base);
}
template<typename Derived,typename Base>
Derived const& crtp_cast(Base const& base){
	return static_cast<Derived const&>(base);
}
template<typename Derived,typename Base>
Derived const* crtp_cast(Base const* base){
	return static_cast<Derived const*>(base);
}
} //namespace util
} //namespace panlib

#endif

