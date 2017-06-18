/*
 * generator_date.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

//#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace hessian {
namespace generator {

void
value_visitor::operator()(const date_t& value)
{
//	static const date_t EPOCH(boost::gregorian::date(1970, 1, 1));
//	const boost::posix_time::time_duration duration = value - EPOCH;

	const std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(value);
	if (minutes == value)
	{
		push_back<std::int8_t>('K');
		push_back<std::int32_t>(minutes.count());
	}
	else
	{
		push_back<std::int8_t>('J');
		push_back<std::int64_t>(value.count());
	}
}

}
}
