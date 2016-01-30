/*
 * date_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/binary.hpp>
#include <chrono>
#include "byte_parser.hpp"

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef std::chrono::system_clock::time_point date_t;

namespace parser {
namespace detail {

//date ::= 'd' b7 b6 b5 b4 b3 b2 b1 b0

const auto date_action = [](auto& ctx)
{
	std::chrono::milliseconds ms(x3::_attr(ctx));
	x3::_val(ctx) = date_t() + ms;
};

const x3::rule<class date_rule, date_t> date_rule("date");

const auto date_rule_def = x3::lit('d') >> x3::big_qword [date_action];

BOOST_SPIRIT_DEFINE(date_rule);

}

using detail::date_rule;

}
}
