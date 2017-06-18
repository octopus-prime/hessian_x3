/*
 * generator_map.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

void
value_visitor::operator()(const map_t& value)
{
	if (!ref(value))
	{
		push_back<std::int8_t>('H');
		for (const map_t::value_type& element : value)
		{
			element.first.visit(*this);
			element.second.visit(*this);
		}
		push_back<std::int8_t>('Z');
	}
}

}
}
