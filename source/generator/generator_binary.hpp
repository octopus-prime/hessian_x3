/*
 * generator_binary.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const binary_t& value)
{
	_data.push_back('\x20' + value.size()); //TODO
	_data.append(value.begin(), value.end());
}

}
}
