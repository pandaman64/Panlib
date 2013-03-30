#ifndef PANLIB_RANGE_MANIP
#define PANLIB_RANGE_MANIP

#include <string>
#include <utility>

#define RANGE_MANIPULATOR(name)\
struct name##_tag{};\
template<typename CharT,typename Traits = std::char_traits<CharT>>\
struct name{\
	using string_type = std::basic_string<CharT,Traits>;\
	string_type str;\
	name(string_type s) : str(std::move(s)){\
	}\
};\
template<typename Stream,typename Char,typename Traits>\
Stream &operator <<(Stream &stream,name<Char,Traits> const& m){\
	ios_manip_data<name##_tag,Stream>(stream).set(m.data());\
	return stream;\
}

namespace panlib{
namespace range{

template<typename Tag,typename Stream,typename T>
struct stream_data{
	static int index;

	struct data_holder{
		T data;
	};

	static void attach(Stream &stream,T data){
		static data_holder holder;
		holder.data = std::move(data);
		stream.pword(index) = &holder.data;
	}

	static T const* get(Stream &stream){
		return static_cast<T const*>(stream.pword(index));
	}
};
template<typename Tag,typename Stream,typename T>
int stream_data<Tag,Stream,T>::index = Stream::xalloc();

template<typename Tag,typename Stream>
struct ios_manip_data{
	using char_type = typename Stream::char_type;
	using traits_type = typename Stream::traits_type;
	using string_type = std::basic_string<char_type,traits_type>;
	using stream_data_type = stream_data<Tag,Stream,string_type>;

	static int index;
	Stream &stream;

	ios_manip_data(Stream &s) : stream(s){
	}

	void set(string_type const& str){
		stream_data_type::attach(str);
	}

	void print(string_type default_){
		auto ptr = stream_data_type::get(stream);
		if(ptr){
			stream << *ptr;
		}
		else{
			stream << default_;
		}
	}
};

RANGE_MANIPULATOR(range_open)
RANGE_MANIPULATOR(range_delimiter)
RANGE_MANIPULATOR(range_close)

} //namespace range
} //namespace panlib

#undef RANGE_MANIPULATOR

#endif

