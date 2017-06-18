/*
 * value.cpp
 *
 *  Created on: 19.02.2016
 *      Author: mike_gresens
 */

#include <hessian/value.hpp>
#include "value/value_output.hpp"

namespace hessian {

std::ostream&
operator<<(std::ostream& stream, const value_t& value)
{
	output_visitor visitor(stream);
	value.visit(visitor);
	return stream;
}

}
