/*
 * generator_long.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const long_t& value)
{
	push_back<std::int8_t>('\xe0' + value); //TODO
}

}
}
