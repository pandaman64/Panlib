#ifndef PANLIB_RANGE_HEADER
#define PANLIB_RANGE_HEADER

#include <cassert>
#include <cstddef>
#include <type_traits>
#include <iterator>

namespace panlib{
namespace range{

namespace detail{

	using std::begin;

	template<typename Seq>
	auto adl_begin(Seq &&seq)
	->decltype(begin(seq));
} //namespace detail

template<typename Iterator>
struct iterator_range{
protected:
	Iterator begin,end;

public:
	using value_type = typename std::remove_reference<decltype(*begin)>::type;
	using reference = value_type&;
	using const_reference = value_type const&;

	iterator_range(Iterator beg,Iterator end) : begin(beg),end(end){}
};

template<typename Iterator>
struct input_iterator_range : iterator_range<Iterator>{
	using base = iterator_range<Iterator>;
	using typename base::value_type;
	using typename base::reference;
	using typename base::const_reference;
	
	input_iterator_range(Iterator beg,Iterator end) : base(beg,end){}

	void pop_front(){
		assert(!this->empty());
		++this->begin;
	}
	reference front(){
		assert(!this->empty());
		return *this->begin;
	}
	bool empty() const{
		return this->begin == this->end;
	}
};

template<typename Iterator>
struct forward_iterator_range : input_iterator_range<Iterator>{
	using base = input_iterator_range<Iterator>;
	using typename base::value_type;
	using typename base::reference;
	using typename base::const_reference;

	forward_iterator_range(Iterator beg,Iterator end) : base(beg,end){}
};

template<typename Iterator>
struct bidirectional_iterator_range : forward_iterator_range<Iterator>{
	using base = forward_iterator_range<Iterator>;
	using typename base::value_type;
	using typename base::reference;
	using typename base::const_reference;

	bidirectional_iterator_range(Iterator beg,Iterator end) : base(beg,end){}
	
	void pop_back(){
		assert(!this->empty());
		--this->end;
	}
	reference back(){
		assert(!this->empty());
		auto it = this->end;
		--it;
		return *it;
	}
};

template<typename Iterator>
struct random_access_iterator_range : bidirectional_iterator_range<Iterator>{
	using base = bidirectional_iterator_range<Iterator>;
	using typename base::value_type;
	using typename base::reference;
	using typename base::const_reference;

	random_access_iterator_range(Iterator beg,Iterator end) : base(beg,end){}

	reference at(std::size_t index){
		return *(this->begin + index);
	}
};

template<typename Iterator,typename Category = typename std::iterator_traits<Iterator>::iterator_category>
struct choose_iterator_range;
template<typename Iterator>
struct choose_iterator_range<Iterator,std::input_iterator_tag>{
	typedef input_iterator_range<Iterator> type;
};
template<typename Iterator>
struct choose_iterator_range<Iterator,std::forward_iterator_tag>{
	typedef forward_iterator_range<Iterator> type;
};
template<typename Iterator>
struct choose_iterator_range<Iterator,std::bidirectional_iterator_tag>{
	typedef bidirectional_iterator_range<Iterator> type;
};
template<typename Iterator>
struct choose_iterator_range<Iterator,std::random_access_iterator_tag>{
	typedef random_access_iterator_range<Iterator> type;
};

template<typename Seq>
auto all(Seq &&seq)
->typename choose_iterator_range<decltype(detail::adl_begin(seq))>::type{
	using std::begin;
	using std::end;
	return { begin(seq),end(seq) };
}

} //namespace range
} //namespace panlib

#endif

