/*
 * null_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/blank.hpp>

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef boost::blank null_t;

namespace parser {
namespace detail {

const x3::rule<class null_rule, null_t> null_rule("null");

const auto null_rule_def = x3::lit('N') >> x3::attr(null_t());

BOOST_SPIRIT_DEFINE(null_rule);

}

using detail::null_rule;

}
}
