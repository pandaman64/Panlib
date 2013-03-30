#include "range.h"
#include "io.h"
#include "concept.h"
#include "extends.h"
#include "../Util/print_type.h"
#include "istream_range.h"

#include <vector>
#include <list>
#include <iostream>

using namespace panlib::range;
using namespace panlib::util;

template<typename Range>
struct negate_range : extends<Range,negate_range<Range>>{
	using base = extends<Range,negate_range<Range>>;
	using value_type = typename base::value_type;
	
	negate_range(Range r) : base(std::move(r)){
	}
	
	value_type front_(){
		return -base::front_();
	}
	value_type back_(){
		return -base::back_();
	}
};

template<typename Range>
negate_range<typename std::remove_reference<Range>::type> make(Range &&range){
	return { range };
}

int main(){
	std::vector<int> v = {1,2,3,4,5};
	std::list<int> l = {1,2,3,4,5};

	auto vv = all(v);
	auto vr = make(all(v));

	std::cout << vr.front() << vr.empty();

	std::cout << vv << std::endl;
	std::cout << vr << std::endl;

	print_type(vv);
	print_type(vr);
	print_range(vv);
	print_range(vr);

	istream_range<int> range{std::cin};
	print_range(range);
}

