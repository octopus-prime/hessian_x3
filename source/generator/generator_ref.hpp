/*
 * generator_ref.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

inline bool
value_visitor::ref(const value_t& value)
{
	const auto ref = std::find(_ref.begin(), _ref.end(), value);
	const bool found = ref != _ref.end();
	if (found)
	{
		const int_t position = std::distance(_ref.begin(), ref);
		push_back<std::int8_t>('Q');
		(*this)(position);
	}
	else
	{
		_ref.push_back(value);
	}
	return found;
}

}
}
