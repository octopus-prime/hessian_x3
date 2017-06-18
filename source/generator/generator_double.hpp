/*
 * generator_double.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

void
value_visitor::operator()(const double_t& value)
{
	double buffer;
	if (std::modf(value, &buffer) == 0.0)
	{
		if (value == 0.0)
		{
			push_back<std::int8_t>('\x5b');
		}
		else if (value == 1.0)
		{
			push_back<std::int8_t>('\x5c');
		}
		else if (value >= std::numeric_limits<std::int8_t>::min() && value <= std::numeric_limits<std::int8_t>::max())
		{
			push_back<std::int8_t>('\x5d');
			push_back<std::int8_t>(value);
		}
		else if (value >= std::numeric_limits<std::int16_t>::min() && value <= std::numeric_limits<std::int16_t>::max())
		{
			push_back<std::int8_t>('\x5e');
			push_back<std::int16_t>(value);
		}
		else
		{
			push_back<std::int8_t>('D');
			push_back<std::int64_t>(*reinterpret_cast<const std::int64_t* const>(&value));
		}
	}
	else
	{
		const double temp = 1000.0 * value;
		if (std::modf(temp, &buffer) == 0.0 && temp >= std::numeric_limits<std::int32_t>::min() && temp <= std::numeric_limits<std::int32_t>::max())
		{
			push_back<std::int8_t>('\x5f');
			push_back<std::int32_t>(temp);
		}
		else
		{
			push_back<std::int8_t>('D');
			push_back<std::int64_t>(*reinterpret_cast<const std::int64_t* const>(&value));
		}
	}
}

}
}
