/*
 * generator_list.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const list_t& value)
{
	if (value.empty()) //TODO
		return;

	push_back<std::int8_t>('\x78' + value.size());
	for (const value_t& element : value)
		boost::apply_visitor(*this, element);
}

}
}
