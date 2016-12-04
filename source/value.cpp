/*
 * value.cpp
 *
 *  Created on: 19.02.2016
 *      Author: mike_gresens
 */

#include <hessian/value.hpp>
#include "value/value_hash.hpp"
#include "value/value_output.hpp"

namespace hessian {

size_t
hash::operator()(const value_t& value) const noexcept
{
	return boost::hash_value(value);
}

std::ostream&
operator<<(std::ostream& stream, const value_t& value)
{
	output_visitor visitor(stream);
	boost::apply_visitor(visitor, value);
	return stream;
}

}
