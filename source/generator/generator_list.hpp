/*
 * generator_list.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

void
value_visitor::operator()(const list_t& value)
{
	if (!ref(value))
	{
		if (value.size() <= 7)
		{
			push_back<std::int8_t>('\x78' + value.size());
			for (const list_t::value_type& element : value)
				element.visit(*this);
		}
		else
		{
			push_back<std::int8_t>('W');
			for (const list_t::value_type& element : value)
				element.visit(*this);
			push_back<std::int8_t>('Z');
		}
	}
}

}
}
