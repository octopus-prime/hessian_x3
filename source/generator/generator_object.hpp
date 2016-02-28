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
	throw std::runtime_error("Not implemented."); //TODO
}

}
}
