#ifndef PANLIB_ET_SUBSCRIPTION
#define PANLIB_ET_SUBSCRIPTION

#include <tuple>
#include <utility>

namespace panlib{
namespace ET{

	template<typename Derived>
	struct expression_base;

namespace subscription_operator{
	template<typename Left,typename Right>
	struct subscription : expression_base<subscription<Left,Right>>{
		using tuple_type = std::tuple<Left&,Right&>;
		using const_tuple_type = std::tuple<Left const&,Right const&>;

		char const* expr_name = "subscription";

		Left left;
		Right right;

		template<typename L,typename R>
		subscription(L &&l,R &&r) : left(std::forward<L>(l)),right(std::forward<R>(r)){
		}

		tuple_type as_tuple(){
			return std::tie(left,right);
		}
		const_tuple_type const as_tuple() const{
			return std::tie(left,right);
		}
	};
} //namespace subscription
} //namespace ET
} //namespace panlib

#endif

