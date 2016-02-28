/*
 * generator_value.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/endian/conversion.hpp>

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

protected:
	template <typename T>
	void push_back(const T value);

	bool ref(const value_t& value);

private:
	std::string& _data;
	list_t _ref;
};

inline
value_visitor::value_visitor(std::string& data)
:
	_data(data)
{
}

template <>
inline void
value_visitor::push_back(const std::int8_t value)
{
	_data.push_back(value);
}

template <typename T>
inline void
value_visitor::push_back(const T value)
{
	const T big = boost::endian::native_to_big(value);
	_data.append(reinterpret_cast<const char* const>(&big), sizeof(T));
}

}
}
