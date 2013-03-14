#ifndef PANLIB_ET_TAG
#define PANLIB_ET_TAG

namespace panlib{
namespace ET{

namespace tag{
	namespace unary_operator{
		struct plus{};
		struct negate{};
		struct dereference{};
		struct complement{};
		struct address_of{};
		struct logical_not{};
		struct prefix_increment{};
		struct prefix_decrement{};
		struct postfix_increment{};
		struct postfix_decrement{};
	} //namespace unary_operator
	namespace binary_operator{
		struct plus{};
		struct minus{};
		struct multiple{};
		struct divide{};
		struct module{};
		struct left_shift{};
		struct right_shift{};
		struct less{};
		struct greater{};
		struct less_equal{};
		struct greater_equal{};
		struct equal_to{};
		struct not_equal_to{};
		struct logical_or{};
		struct logical_and{};
		struct bitwise_or{};
		struct bitwise_and{};
		struct bitwise_xor{};
		struct assign{};
		struct plus_assign{};
		struct minus_assign{};
		struct multiple_assign{};
		struct divide_assign{};
		struct module_assign{};
		struct left_shift_assign{};
		struct right_shift_assign{};
		struct bitwise_or_assign{};
		struct bitwise_and_assign{};
		struct bitwise_xor_assign{};
		struct comma{};
		struct member_pointer{};
		struct subscription{};
	} //namespace binary_operator
	namespace function_call{
		struct function{};
	} //namespace function_call
	struct terminal{};
}
} //namespace ET
} //namespace panlib

#endif

