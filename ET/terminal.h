#ifndef PANLIB_ET_TERMINAL
#define PANLIB_ET_TERMINAL

#include <utility>
#include <tuple>

#include "expression_base.h"

namespace panlib{
namespace ET{
	template<typename T>
	struct terminal : expression_base<terminal<T>>{
	private:
		T value;

	public:
		using tuple_type = std::tuple<T&>;
		using const_tuple_type = std::tuple<T const&>;

		char const* expr_name = "terminal";

		template<typename U>
		terminal(U &&v) : value(std::forward<U>(v)){
		}

		tuple_type as_tuple(){
			return std::tie(value);
		}
		const_tuple_type const as_tuple() const{
			return std::tie(value);
		}
	};

} //namespace ET
} //namespace panlib

#endif

