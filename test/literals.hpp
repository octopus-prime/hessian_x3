/*
 * literals.hpp
 *
 *  Created on: 13.12.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/date_time/posix_time/time_parsers.hpp>
#include <sstream>

using namespace std::literals;

namespace hessian {

inline binary_t
operator"" _b(const char* s, const size_t l)
{
    return binary_t(reinterpret_cast<const unsigned char*>(s), l);
}

inline date_t
operator"" _d(const char* s, const size_t l)
{
	using boost::posix_time::from_iso_string;
    return from_iso_string(string_t(s, l));
}

inline int_t
operator"" _i(const unsigned long long v)
{
	return static_cast<int_t>(v);
}

inline long_t
operator"" _l(const unsigned long long v)
{
	return static_cast<long_t>(v);
}

}
