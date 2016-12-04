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

using null_t = boost::blank;
using bool_t = bool;
using int_t = std::int32_t;
using long_t = std::int64_t;
using double_t = double;
using date_t = boost::posix_time::ptime;
using string_t = std::string;
using binary_t = std::basic_string<std::uint8_t>;

template <typename T>
using basic_list_t = std::vector<T>;
template <typename T>
using basic_map_t = std::unordered_map<T, T, hash>;
template <typename T>
using basic_object_t = std::unordered_map<string_t, T>;

using value_t = boost::make_recursive_variant<
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
>::type;

using list_t = basic_list_t<value_t>;
using map_t = basic_map_t<value_t>;
using object_t = basic_object_t<value_t>;

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
