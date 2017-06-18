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

class value_visitor
{
	using ref_t = list_t;
	using def_t = std::vector<std::vector<string_t>>;

public:
	value_visitor(std::string& data);
	void operator()(const null_t& value);
	void operator()(const bool_t& value);
	void operator()(const int_t& value);
	void operator()(const long_t& value);
	void operator()(const double_t& value);
	void operator()(const date_t& value);
	void operator()(const string_t& value);
	void operator()(const binary_t& value);
	void operator()(const list_t& value);
	void operator()(const map_t& value);
	void operator()(const object_t& value);

protected:
	template <typename T>
	void push_back(const T value);

	bool ref(const value_t& value);
	int_t def(const object_t& value);

private:
	std::string& _data;
	ref_t _ref;
	def_t _def;
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
