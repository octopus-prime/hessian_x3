/*
 * value.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/blank.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/variant.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

namespace hessian {

typedef boost::blank null_t;
typedef bool bool_t;
typedef std::int32_t int_t;
typedef std::int64_t long_t;
typedef double double_t;
typedef boost::posix_time::ptime date_t;
typedef std::string string_t;

typedef boost::make_recursive_variant
<
	null_t,
	bool_t,
	int_t,
	long_t,
	double_t,
	date_t,
	string_t,
//	binary_t,
	std::vector<boost::recursive_variant_>									// list_t
//	std::map<boost::recursive_variant_, boost::recursive_variant_, less>,	// map_t
//	boost::unordered_map<string_t, boost::recursive_variant_>				// object_t
>::type value_t;

typedef std::vector<value_t> list_t;

}

namespace std {

inline ostream&
operator<<(ostream& stream, const hessian::list_t& list)
{
	for (const hessian::value_t& value : list)
		stream << value << ", ";
	return stream;
}

}
