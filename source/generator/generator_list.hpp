/*
 * generator_list.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const list_t& value)
{
	if (value.empty()) //TODO
		return;
	_data.push_back('\x78' + value.size());
	for (const auto& element : value)
		boost::apply_visitor(*this, element);
}

}
}
