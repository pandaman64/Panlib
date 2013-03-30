#ifndef PANLIB_RANGE_IO
#define PANLIB_RANGE_IO

#include <iostream>
#include <type_traits>

#include "manip.h"
#include "concept.h"

#include "../Util/print_type.h"

namespace panlib{
namespace range{

namespace operators{
	template<typename Stream,typename Range,typename std::enable_if<concept::is_forward_range<Range>{}>::type* = nullptr>
	Stream &operator <<(Stream &stream,Range range){
		struct brace_printer{
			Stream &os;

			brace_printer(Stream &s) : os(s){
				ios_manip_data<range_open_tag,Stream>(os).print("[");
			}
			~brace_printer(){
				ios_manip_data<range_close_tag,Stream>(os).print("]");
			}
		} printer(stream);

		if(range.empty()){
			return stream;
		}

		stream << range.front();
		range.pop_front();
		while(!range.empty()){
			ios_manip_data<range_delimiter_tag,Stream>(stream).print(",");
			stream << range.front();
			range.pop_front();
		}

		return stream;
	}
}

template<typename Range>
void print_range(Range &&range){
	std::cout << range << std::endl;
}

} //namespace range
} //namespace panlib

#endif

