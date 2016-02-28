/*
 * generator_date.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace hessian {
namespace generator {

value_visitor::result_type
value_visitor::operator()(const date_t& value)
{
	static const date_t EPOCH(boost::gregorian::date(1970, 1, 1));
	const boost::posix_time::time_duration duration = value - EPOCH;
	if (duration.get_rep() % boost::posix_time::minutes(1).get_rep() == 0)
	{
		push_back<std::int8_t>('K');
		push_back<std::int32_t>(duration.minutes());
	}
	else
	{
		push_back<std::int8_t>('J');
		push_back<std::int64_t>(duration.total_milliseconds());
	}
}

}
}
