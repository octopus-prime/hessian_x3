/*
 * parser.cpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#include <hessian/parser.hpp>
#include "parser/parser_value.hpp"
#include <boost/spirit/include/support_istream_iterator.hpp>

using namespace std::literals;

namespace hessian {

const char*
parse_exception::what() const noexcept
{
	return "Parsing failed.";
}

namespace parser {

const x3::rule<class content_rule, content_t> content_rule;
const x3::rule<class reply_rule, reply_t> reply_rule;
const x3::rule<class fault_rule, fault_t> fault_rule;

const auto content_rule_def = x3::lit('H') >> x3::lit('\x02') >> x3::lit('\x00') >> (reply_rule | fault_rule);
const auto reply_rule_def = x3::lit('R') >> value_rule;
const auto fault_rule_def = x3::lit('F') >> map_rule;

BOOST_SPIRIT_DEFINE(content_rule, reply_rule, fault_rule);

}

content_t
parse(const std::string& stream)
{
	std::string::const_iterator begin(stream.begin()), end(stream.end());
	parser::def_t def;
	parser::ref_t ref;
	const auto rule = x3::with<parser::def_tag>(std::ref(def)) [ x3::with<parser::ref_tag>(std::ref(ref)) [parser::content_rule] ];
	content_t content;

	const bool ok = x3::parse(begin, end, rule, content);
	if (!ok || begin != end)
		throw parse_exception();

	return content;
}

}
