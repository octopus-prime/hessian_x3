/*
 * sample.hpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string/erase.hpp>
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

inline string_t
make_string_1024()
{
	boost::format f("%02d 456789012345678901234567890123456789012345678901234567890123\n");

	string_t value;
	for (std::size_t i = 0; i < 16; i++)
		value += (f % i).str();
	return value;
}

inline string_t
make_string_1023()
{
	return boost::algorithm::erase_tail_copy(make_string_1024(), 1);
}

inline string_t
make_string_65536()
{
	boost::format f("%03d 56789012345678901234567890123456789012345678901234567890123\n");

	string_t value;
	for (std::size_t j = 0; j < 2; j++)
		for (std::size_t i = 0; i < 32 * 16; i++)
			value += (f % i).str();
	return value;
}

inline string_t
make_string_65535()
{
	return boost::algorithm::erase_tail_copy(make_string_65536(), 1);
}

typedef std::pair<string_t, value_t> sample_t;
typedef std::vector<sample_t> success_samples_t;
typedef std::vector<string_t> failure_samples_t;

}

namespace std {

inline ostream&
operator<<(ostream& stream, const hessian::sample_t& sample)
{
	stream << boost::algorithm::hex(sample.first) << " & " << sample.second;
	return stream;
}

}
