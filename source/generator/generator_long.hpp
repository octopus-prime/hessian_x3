/*
 * generator_long.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const long_t& value)
{
	if (value >= -8 && value <= 15)
	{
		push_back<std::int8_t>('\xe0' + value);
	}
	else if (value >= -0x800 && value <= 0x7ff)
	{
		push_back<std::int8_t>('\xf8' + (value >> 8));
		push_back<std::int8_t>(value & 0xff);
	}
	else if (value >= -0x40000 && value <= 0x3ffff)
	{
		push_back<std::int8_t>('\x3c' + (value >> 16));
		push_back<std::int16_t>(value & 0xffff);
	}
	else if (value >= -0x80000000LL && value <= 0x7fffffffLL)
	{
		push_back<std::int8_t>('Y');
		push_back<std::int32_t>(value);
	}
	else
	{
		push_back<std::int8_t>('L');
		push_back<std::int64_t>(value);
	}
}

}
}
