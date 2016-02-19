/*
 * value.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/blank.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/variant.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace hessian {

struct hash;

typedef boost::blank null_t;
typedef bool bool_t;
typedef std::int32_t int_t;
typedef std::int64_t long_t;
typedef double double_t;
typedef boost::posix_time::ptime date_t;
typedef std::string string_t;
typedef std::basic_string<std::uint8_t> binary_t;

typedef boost::make_recursive_variant
<
	null_t,
	bool_t,
	int_t,
	long_t,
	double_t,
	date_t,
	string_t,
	binary_t,
	std::vector<boost::recursive_variant_>,											// list_t
	std::unordered_map<boost::recursive_variant_, boost::recursive_variant_, hash>,	// map_t
	std::unordered_map<string_t, boost::recursive_variant_>							// object_t
>::type value_t;

struct hash
{
	size_t operator()(const value_t& value) const;
};

typedef std::vector<value_t> list_t;
typedef std::unordered_map<value_t, value_t, hash> map_t;
typedef std::unordered_map<string_t, value_t> object_t;

std::ostream& operator<<(std::ostream& stream, const value_t& value);

}
