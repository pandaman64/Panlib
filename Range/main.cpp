#include "range.h"
#include "io.h"
#include "concept.h"
#include "extends.h"

#include <vector>
#include <list>
#include <iostream>

using namespace panlib::range;
using namespace panlib::util;

template<typename Range>
struct negate_range : extends<Range,negate_range<Range>>{
	using base = extends<Range,negate_range<Range>>;
	negate_range(Range r) : base(std::move(r)){
	}
	
	template<typename T>
	typename std::remove_reference<T>::type transform(T &&value){
		return -value;
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

	print_range(vv);
	print_range(vr);
}

