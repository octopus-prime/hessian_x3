/*
 * value_hash.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/variant/detail/hash_variant.hpp>
#include <boost/functional/hash.hpp>

namespace boost {

size_t
hash_value(const hessian::null_t& value)
{
	return 0xAAAAAAAAAAAAAAAA;
}

size_t
hash_value(const hessian::date_t& value)
{
	size_t seed = 0;
	hash_combine(seed, value.date().day_count().as_number());
	hash_combine(seed, value.time_of_day().total_milliseconds());
    return seed;
}

size_t
hash_value(const hessian::map_t& value)
{
	return boost::hash_range(value.begin(), value.end());
}

size_t
hash_value(const hessian::object_t& value)
{
	return boost::hash_range(value.begin(), value.end());
}

}
