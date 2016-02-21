/*
 * test_date.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <hessian/parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/date_time.hpp>
#include "sample.hpp"

using boost::posix_time::from_iso_string;

namespace hessian {
namespace parser {

date_t operator"" _d(const char* s, const size_t l)
{
    return from_iso_string(string_t(s, s + l));
}

const success_samples_t success_samples
{
	{"K\x00\x00\x00\x00"s, "19700101T000000"_d},
	{"K\x00\xe3\x83\x8f"s, "19980508T095100"_d},
	{"J\x00\x00\x00\xd0\x4b\x92\x84\xb8"s, "19980508T095131"_d}
};

BOOST_AUTO_TEST_SUITE(test_date)

BOOST_DATA_TEST_CASE(test, success_samples, sample)
{
	std::istringstream stream(sample.first);
	value_t value;

	BOOST_REQUIRE_NO_THROW(value = parse(stream));
	BOOST_CHECK_EQUAL(value, sample.second);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
