/*
 * generator_def.hpp
 *
 *  Created on: 28.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <functional>

namespace hessian {
namespace generator {

inline int_t
value_visitor::def(const object_t& value)
{
	def_t::value_type members;
	std::transform
	(
		value.begin(), value.end(),
		std::back_inserter(members),
		std::bind(&object_t::value_type::first, std::placeholders::_1)
	);
	const auto def = std::find(_def.begin(), _def.end(), members);
	const bool found = def != _def.end();
	if (found)
	{
		return std::distance(_def.begin(), def);
	}
	else
	{
		push_back<std::int8_t>('C');
		push_back<std::int8_t>('\x00');
		(*this)(static_cast<int_t>(members.size()));
		for (const string_t& member : members)
			(*this)(member);
		_def.push_back(members);
		return _def.size() - 1;
	}
}

}
}
