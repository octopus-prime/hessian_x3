/*
 * generator_binary.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

void
value_visitor::operator()(const binary_t& value)
{
	auto iterator = value.begin();

	while (std::distance(iterator, value.end()) > 0xffff)
	{
		push_back<std::int8_t>('A');
		push_back<std::int16_t>(0xffff);
		_data.append(iterator, iterator + 0xffff);
		iterator += 0xffff;
	}

	const int_t length = std::distance(iterator, value.end());

	if (length <= 15)
	{
		push_back<std::int8_t>('\x20' + length);
	}
	else if(length <= 1023)
	{
		push_back<std::int8_t>('\x34' + (length >> 8));
		push_back<std::int8_t>(length & 0xff);
	}
	else
	{
		push_back<std::int8_t>('B');
		push_back<std::int16_t>(length);
	}

	_data.append(iterator, value.end());
}

}
}
