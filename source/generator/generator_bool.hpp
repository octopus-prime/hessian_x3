/*
 * generator_bool.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const bool_t& value)
{
	constexpr char bools[] = {'T', 'F'};
	_data.push_back(bools[value]);
}

}
}
