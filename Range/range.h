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

	template<typename T>
	struct dereferenced_type{
		typedef decltype(*std::declval<T>()) type;
	};
} //namespace detail

template<typename Iterator>
struct iterator_range{
private:
	Iterator begin,end;

public:
	typedef typename detail::dereferenced_type<Iterator>::type value_type;

	iterator_range(Iterator beg,Iterator end) : begin(beg),end(end){}

	void pop_front(){
		assert(!empty());
		++begin;
	}
	void pop_back(){
		assert(!empty());
		--end;
	}

	value_type front(){
		assert(!empty());
		return *begin;
	}
	value_type back(){
		assert(!empty());
		auto it = end;
		--it;
		return *it;
	}
	value_type at(std::size_t index){
		return *(begin + index);
	}

	bool empty() const{
		return begin == end;
	}
};

template<typename Iterator>
struct input_iterator_range : iterator_range<Iterator>{
	typedef iterator_range<Iterator> base;

	input_iterator_range(Iterator beg,Iterator end) : base(beg,end){}

	using base::pop_front;
	using base::front;
	using base::empty;
};

template<typename Iterator>
struct forward_iterator_range : iterator_range<Iterator>{
	typedef iterator_range<Iterator> base;

	forward_iterator_range(Iterator beg,Iterator end) : base(beg,end){}

	using base::pop_front;
	using base::front;
	using base::empty;
};

template<typename Iterator>
struct bidirectional_iterator_range : iterator_range<Iterator>{
	typedef iterator_range<Iterator> base;

	bidirectional_iterator_range(Iterator beg,Iterator end) : base(beg,end){}

	using base::pop_front;
	using base::pop_back;
	using base::front;
	using base::back;
	using base::empty;
};

template<typename Iterator>
struct random_access_iterator_range : iterator_range<Iterator>{
	typedef iterator_range<Iterator> base;

	random_access_iterator_range(Iterator beg,Iterator end) : base(beg,end){}

	using base::pop_front;
	using base::pop_back;
	using base::front;
	using base::back;
	using base::at;
	using base::empty;
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
auto all(Seq seq)
->typename choose_iterator_range<decltype(detail::adl_begin(seq))>::type{
	using std::begin;
	using std::end;
	return { begin(seq),end(seq) };
}

} //namespace range
} //namespace panlib

#endif
