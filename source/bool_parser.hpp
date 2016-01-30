/*
 * bool_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef bool bool_t;

namespace parser {
namespace detail {

//boolean ::= T
//        ::= F

// x3::symbols<bool> const bool_rule({{"T", true}, {"F", false}}, "bool");

const x3::rule<class bool_rule, bool_t> bool_rule("bool");
const x3::rule<class true_rule, bool_t> true_rule;
const x3::rule<class false_rule, bool_t> false_rule;

const auto bool_rule_def = true_rule | false_rule;
const auto true_rule_def = x3::lit('T') >> x3::attr(true);
const auto false_rule_def = x3::lit('F') >> x3::attr(false);

BOOST_SPIRIT_DEFINE(bool_rule, true_rule, false_rule);

}

using detail::bool_rule;

}
}
