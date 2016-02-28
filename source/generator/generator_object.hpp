/*
 * generator_object.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const object_t& value)
{
	if (!ref(value))
	{
		const int_t index = def(value);
		if (index <= 15)
		{
			push_back<std::int8_t>('\x60' + index);
		}
		else
		{
			push_back<std::int8_t>('O');
			(*this)(index);
		}
		for (const object_t::value_type& element : value)
			boost::apply_visitor(*this, element.second);
	}
}

}
}
