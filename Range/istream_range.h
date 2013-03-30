#ifndef PANLIB_RANGE_ISTREAM_RANGE
#define PANLIB_RANGE_ISTREAM_RANGE

#include <iosfwd>
#include <iterator>

#include "range.h"

namespace panlib{
namespace range{

template<typename T,typename CharT = char,typename Traits = std::char_traits<CharT>,typename Diff = std::ptrdiff_t>
struct istream_range : input_iterator_range<std::istream_iterator<T,CharT,Traits,Diff>>{
	using iterator_type = std::istream_iterator<T,CharT,Traits,Diff>;
	using base = input_iterator_range<iterator_type>;

	istream_range(std::basic_istream<CharT,Traits> &stream) : base(iterator_type(stream),iterator_type()){
	}
};

} //namespace range
} //namespace panlib

#endif

