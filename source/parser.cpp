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

const char*
parse_exception::what() const noexcept
{
	return "Parsing failed.";
}

value_t
parse(std::istream& stream)
{
	stream.unsetf(std::ios::skipws);

	boost::spirit::istream_iterator begin(stream), end;
	parser::def_t def;
	parser::ref_t ref;
	const auto rule = x3::with<parser::def_tag>(std::ref(def)) [ x3::with<parser::ref_tag>(std::ref(ref)) [parser::value_rule] ];
	value_t value;

	const bool ok = x3::parse(begin, end, rule, value);
	if (!ok || begin != end)
		throw parse_exception();

	return value;
}

//value_t
//parse(const std::string& stream)
//{
//	std::string::const_iterator begin(stream.begin()), end(stream.end());
//	parser::def_t def;
//	parser::ref_t ref;
//	const auto rule = x3::with<parser::def_tag>(std::ref(def)) [ x3::with<parser::ref_tag>(std::ref(ref)) [parser::value_rule] ];
//	value_t value;
//
//	const bool ok = x3::parse(begin, end, rule, value);
//	if (!ok || begin != end)
//		throw parse_exception();
//
//	return value;
//}

}
