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

template <typename Duration>
struct date_action
{
	void operator()(auto& ctx) const
	{
		static const date_t EPOCH(boost::gregorian::date(1970, 1, 1));
		x3::_val(ctx) = EPOCH + Duration(x3::_attr(ctx));
	};
};

const x3::rule<class date_rule, date_t> date_rule("date");
const x3::rule<class date1_rule, date_t> date1_rule;
const x3::rule<class date2_rule, date_t> date2_rule;

const auto date_rule_def = date1_rule | date2_rule;
const auto date1_rule_def = x3::lit('J') >> x3::big_qword [date_action<boost::posix_time::milliseconds>()];
const auto date2_rule_def = x3::lit('K') >> x3::big_dword [date_action<boost::posix_time::minutes>()];

BOOST_SPIRIT_DEFINE(date_rule, date1_rule, date2_rule);

}

using detail::date_rule;

}
}
