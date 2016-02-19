/*
 * parser.cpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#include <hessian/parser.hpp>
#include "parser/parser_value.hpp"
#include <boost/spirit/include/support_istream_iterator.hpp>

namespace hessian {

value_t
parse(std::istream& stream)
{
	stream.unsetf(std::ios::skipws);

	boost::spirit::istream_iterator begin(stream), end;
	value_t value;

	const bool ok = x3::parse(begin, end, parser::value_rule, value);
	if (!ok || begin != end)
		throw std::runtime_error("Parsing failed.");

	return value;
}

//value_t
//parse(const std::string& stream)
//{
//	std::string::const_iterator begin(stream.begin()), end(stream.end());
//	value_t value;
//
//	const bool ok = x3::parse(begin, end, parser::value_rule, value);
//	if (!ok || begin != end)
//		throw std::runtime_error("Parsing failed.");
//
//	return value;
//}

}