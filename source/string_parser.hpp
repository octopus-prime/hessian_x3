/*
 * string_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/binary.hpp>
#include <string>
#include <memory>
#include "byte_parser.hpp"

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef std::string string_t;

namespace parser {
namespace detail {

//string ::= s b1 b0 <utf8-data> string
//       ::= S b1 b0 <utf8-data>
//       ::= [x00-x1f] <utf8-data>

// NOTE: The length means number of UTF16 characters but the content is given in UTF8 characters!

struct length_tag;
const auto length_action = [](auto& ctx)
{
	*x3::get<length_tag>(ctx) = x3::_attr(ctx);
};
const auto more_action = [](auto &ctx)
{
	x3::_pass(ctx) = *x3::get<length_tag>(ctx) >  x3::_val(ctx).size();
};
const auto done_action = [](auto &ctx)
{
	x3::_pass(ctx) = *x3::get<length_tag>(ctx) == x3::_val(ctx).size();
};
const auto push_action = [](auto &ctx)
{
	x3::_val(ctx).push_back(x3::_attr(ctx));
};

const x3::rule<class string_rule, string_t> string_rule("string");
const x3::rule<class string1_rule, string_t> string1_rule;
const x3::rule<class string2_rule, string_t> string2_rule;

const auto string_rule_def = x3::with<length_tag>(std::make_shared<std::size_t>())[string1_rule];
const auto string1_rule_def = x3::lit('S') >> x3::omit[x3::big_word [length_action] ] >> x3::lexeme[ *(x3::eps [more_action] >> x3::char_ [push_action]) >> x3::eps [done_action] ];
const auto string2_rule_def = x3::lit('s') >> x3::omit[x3::big_word [length_action] ] >> x3::lexeme[ *(x3::eps [more_action] >> x3::char_ [push_action]) >> x3::eps [done_action] ] >> string_rule;

BOOST_SPIRIT_DEFINE(string_rule, string1_rule, string2_rule);

}

using detail::string_rule;

}
}
