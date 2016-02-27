/*
 * generator_string.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const string_t& value)
{
	_data.push_back('\x00' + value.size()); //TODO
	_data.append(value);
}

}
}
