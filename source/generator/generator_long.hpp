/*
 * generator_long.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const long_t& value)
{
	_data.push_back('\xe0' + value); //TODO
}

}
}
