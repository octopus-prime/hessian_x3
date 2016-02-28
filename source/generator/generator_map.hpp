/*
 * generator_map.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const map_t& value)
{
	if (!ref(value))
	{
		push_back<std::int8_t>('H');
		for (const map_t::value_type& element : value)
		{
			boost::apply_visitor(*this, element.first);
			boost::apply_visitor(*this, element.second);
		}
		push_back<std::int8_t>('Z');
	}
}

}
}
