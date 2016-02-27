/*
 * generator_null.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const null_t& value)
{
	_data.push_back('N');
}

}
}
