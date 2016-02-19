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
	std::vector<boost::recursive_variant_>,											// list_t
	std::unordered_map<boost::recursive_variant_, boost::recursive_variant_, hash>	// map_t
//	boost::unordered_map<string_t, boost::recursive_variant_>						// object_t
>::type value_t;

//template<>
//struct hash<hessian::value_t>
struct hash
{
	size_t operator()(const value_t& value) const
	{
		return 0;
	}
};

typedef std::vector<value_t> list_t;
typedef std::unordered_map<value_t, value_t, hash> map_t;

}

namespace std {

template<>
struct hash<hessian::value_t>
{
	size_t operator()(const hessian::value_t& value) const
	{
		return 0;
	}
};

template<>
struct __is_fast_hash<hash<hessian::value_t>> : std::false_type
{
};

inline ostream&
operator<<(ostream& stream, const hessian::list_t& list)
{
	for (const hessian::list_t::value_type& value : list)
		stream << value << ", ";
	return stream;
}

inline ostream&
operator<<(ostream& stream, const hessian::map_t& list)
{
	for (const hessian::map_t::value_type& value : list)
		stream << '{' << value.first << " = " << value.second << "}, ";
	return stream;
}

}
