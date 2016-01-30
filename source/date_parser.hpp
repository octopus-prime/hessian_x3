/*
 * date_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/binary.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "byte_parser.hpp"

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef boost::posix_time::ptime date_t;

namespace parser {
namespace detail {

//date ::= 'd' b7 b6 b5 b4 b3 b2 b1 b0

const auto date_action = [](auto& ctx)
{
	static const date_t EPOCH(boost::gregorian::date(1970, 1, 1));
	x3::_val(ctx) = EPOCH + boost::posix_time::milliseconds(x3::_attr(ctx));
};

const x3::rule<class date_rule, date_t> date_rule("date");

const auto date_rule_def = x3::lit('d') >> x3::big_qword [date_action];

BOOST_SPIRIT_DEFINE(date_rule);

}

using detail::date_rule;

}
}
