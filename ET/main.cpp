#include "expression.h"

#include <tuple>

#include "../Util/print_type.h"

struct negate_context : panlib::ET::callable_context<negate_context>{
	template<typename Expr,typename Context>
	auto operator ()(panlib::ET::tag::binary_operator::minus,Expr &&expr,Context &ctx)
	->decltype(evaluate(left(expr),ctx) + evaluate(right(expr),ctx)){
		return evaluate(left(expr),ctx) + evaluate(right(expr),ctx);
	}
};

struct subscription_context : panlib::ET::callable_context<subscription_context>{
	template<typename Expr,typename Context>
	auto operator ()(panlib::ET::tag::binary_operator::subscription,Expr &&expr,Context &ctx)
	->decltype(evaluate(left(expr),ctx)[0]){
		auto const array_size = sizeof(decltype(evaluate(left(expr),ctx))) / sizeof(decltype(evaluate(left(expr),ctx)[0]));
		auto &&_right = evaluate(right(expr),ctx);
		auto &&_left = evaluate(left(expr),ctx);
		return _right < 0 ? _left[array_size + _right] : _left[_right];
	}
};

int main(){
	using namespace panlib::ET;
	using namespace panlib::ET::operators;
	using namespace panlib::util;
	using std::get;

	auto expr = lit(3) + 6 - 7;
	print_type(expr);
	print_expr(expr);

	default_context ctx;
	std::cout << evaluate(lit(5)-6+2,ctx) << std::endl;

	negate_context nctx;
	std::cout << evaluate(lit(5)-6+2,nctx) << std::endl;
	
	subscription_context sctx;
	char str[] = "Hello, World!";
	std::cout << "str[3]=" << evaluate(lit(str)[3],sctx) << " str[-2]=" << evaluate(lit(str)[-2],sctx) << std::endl;

	null_context null_ctx;
	print_type<decltype(evaluate(lit(1)+2+3+4+5,null_ctx))>();

	return 0;
}

