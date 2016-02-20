/*
 * value_output.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/algorithm/hex.hpp>

namespace hessian {

class output_visitor
:
	public boost::static_visitor<>
{
public:
	output_visitor(std::ostream& stream);
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
	std::ostream& _stream;
};

output_visitor::output_visitor(std::ostream& stream)
:
	boost::static_visitor<>(),
	_stream(stream)
{
}

output_visitor::result_type
output_visitor::operator()(const null_t& value)
{
	_stream << "null";
}

output_visitor::result_type
output_visitor::operator()(const bool_t& value)
{
	_stream << "bool(" << std::boolalpha << value << std::noboolalpha << ')';
}

output_visitor::result_type
output_visitor::operator()(const int_t& value)
{
	_stream << "int(" << value << ')';
}

output_visitor::result_type
output_visitor::operator()(const long_t& value)
{
	_stream << "long(" << value << ')';
}

output_visitor::result_type
output_visitor::operator()(const double_t& value)
{
	_stream << "double(" << value << ')';
}

output_visitor::result_type
output_visitor::operator()(const date_t& value)
{
	_stream << "date(" << boost::posix_time::to_iso_extended_string(value) << ')';
}

output_visitor::result_type
output_visitor::operator()(const string_t& value)
{
	_stream << "string('" << value << "')";
}

output_visitor::result_type
output_visitor::operator()(const binary_t& value)
{
	_stream << "binary('";
	boost::algorithm::hex(value, std::ostream_iterator<char>(_stream));
	_stream << "')";
}

output_visitor::result_type
output_visitor::operator()(const list_t& value)
{
	_stream << "list(";
	for (list_t::const_iterator element = value.begin(); element != value.end(); ++element)
	{
		if (element != value.begin())
			_stream << ", ";
		boost::apply_visitor(*this, *element);
	}
	_stream << ')';
}

output_visitor::result_type
output_visitor::operator()(const map_t& value)
{
	_stream << "map(";
	for (map_t::const_iterator element = value.begin(); element != value.end(); ++element)
	{
		if (element != value.begin())
			_stream << ", ";
		boost::apply_visitor(*this, element->first);
		_stream << " = ";
		boost::apply_visitor(*this, element->second);
	}
	_stream << ')';
}

output_visitor::result_type
output_visitor::operator()(const object_t& value)
{
	_stream << "object(";
	for (object_t::const_iterator element = value.begin(); element != value.end(); ++element)
	{
		if (element != value.begin())
			_stream << ", ";
		(*this)(element->first);
		_stream << " = ";
		boost::apply_visitor(*this, element->second);
	}
	_stream << ')';
}

}
