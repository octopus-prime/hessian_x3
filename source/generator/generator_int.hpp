/*
 * generator_int.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

void
value_visitor::operator()(const int_t& value)
{
	if (value >= -16 && value <= 47)
	{
		push_back<std::int8_t>('\x90' + value);
	}
	else if (value >= -0x800 && value <= 0x7ff)
	{
		push_back<std::int8_t>('\xc8' + (value >> 8));
		push_back<std::int8_t>(value & 0xff);
	}
	else if (value >= -0x40000 && value <= 0x3ffff)
	{
		push_back<std::int8_t>('\xd4' + (value >> 16));
		push_back<std::int16_t>(value & 0xffff);
	}
	else
	{
		push_back<std::int8_t>('I');
		push_back<std::int32_t>(value);
	}
}

}
}
