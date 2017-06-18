/*
 * value_output.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/algorithm/hex.hpp>
#include <iomanip>

namespace hessian {

class output_visitor
{
public:
	output_visitor(std::ostream& stream);
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

private:
	std::ostream& _stream;
};

output_visitor::output_visitor(std::ostream& stream)
:
	_stream(stream)
{
}

void
output_visitor::operator()(const null_t& value)
{
	_stream << "null";
}

void
output_visitor::operator()(const bool_t& value)
{
	_stream << "bool(" << std::boolalpha << value << std::noboolalpha << ')';
}

void
output_visitor::operator()(const int_t& value)
{
	_stream << "int(" << value << ')';
}

void
output_visitor::operator()(const long_t& value)
{
	_stream << "long(" << value << ')';
}

void
output_visitor::operator()(const double_t& value)
{
	_stream << "double(" << value << ')';
}

void
output_visitor::operator()(const date_t& value)
{
	using clock = std::chrono::system_clock;
	constexpr clock::time_point epoch;
	const std::time_t time = clock::to_time_t(epoch + value);
	_stream << "date(" << std::put_time(std::gmtime(&time), "%FT%T") << ')';
}

void
output_visitor::operator()(const string_t& value)
{
	_stream << "string('" << value << "')";
}

void
output_visitor::operator()(const binary_t& value)
{
	_stream << "binary('";
	boost::algorithm::hex(value, std::ostream_iterator<char>(_stream));
	_stream << "')";
}

void
output_visitor::operator()(const list_t& value)
{
	_stream << "list(";
	for (list_t::const_iterator element = value.begin(); element != value.end(); ++element)
	{
		if (element != value.begin())
			_stream << ", ";
		element->visit(*this);
	}
	_stream << ')';
}

void
output_visitor::operator()(const map_t& value)
{
	_stream << "map(";
	for (map_t::const_iterator element = value.begin(); element != value.end(); ++element)
	{
		if (element != value.begin())
			_stream << ", ";
		element->first.visit(*this);
		_stream << " = ";
		element->second.visit(*this);
	}
	_stream << ')';
}

void
output_visitor::operator()(const object_t& value)
{
	_stream << "object(";
	for (object_t::const_iterator element = value.begin(); element != value.end(); ++element)
	{
		if (element != value.begin())
			_stream << ", ";
		(*this)(element->first);
		_stream << " = ";
		element->second.visit(*this);
	}
	_stream << ')';
}

}
