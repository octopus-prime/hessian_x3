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
//#include <functional>
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

template <typename T>
using basic_list_t = std::vector<T>;

template <typename T>
using basic_map_t = std::unordered_map<T, T, hash>;

template <typename T>
using basic_object_t = std::unordered_map<string_t, T>;

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
	basic_list_t<boost::recursive_variant_>,
	basic_map_t<boost::recursive_variant_>,
	basic_object_t<boost::recursive_variant_>
>::type value_t;

typedef basic_list_t<value_t> list_t;
typedef basic_map_t<value_t> map_t;
typedef basic_object_t<value_t> object_t;

struct hash
{
	size_t operator()(const value_t& value) const noexcept;
};

std::ostream& operator<<(std::ostream& stream, const value_t& value);

}

namespace std {
	template <>
	struct __is_fast_hash<hessian::hash> : std::false_type { };
}
