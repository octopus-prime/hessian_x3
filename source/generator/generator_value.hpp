/*
 * generator_value.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

namespace hessian {
namespace generator {

class value_visitor : public boost::static_visitor<>
{
public:
	value_visitor(std::string& data);
	result_type operator()(const null_t& value);
	result_type operator()(const bool_t& value);
	result_type operator()(const int_t& value);
	result_type operator()(const long_t& value);
	result_type operator()(const double_t& value);
	result_type operator()(const date_t& value);
	result_type operator()(const string_t& value);
	result_type operator()(const binary_t& value);
	result_type operator()(const list_t& value);
	result_type operator()(const map_t& value);
	result_type operator()(const object_t& value);

private:
	std::string& _data;
};

value_visitor::value_visitor(std::string& data)
:
	_data(data)
{
}

}
}
