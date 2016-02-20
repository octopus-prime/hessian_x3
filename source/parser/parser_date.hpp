/*
 * parser_date.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace hessian {
namespace parser {
namespace date {

static const date_t EPOCH(boost::gregorian::date(1970, 1, 1));

template <typename Duration>
struct date_action
{
	template <typename C>
	void operator()(C& ctx) const
	{
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

using date::date_rule;

}
}
