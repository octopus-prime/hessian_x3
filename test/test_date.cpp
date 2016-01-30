/*
 * test_date.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <date_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "sample.hpp"

using namespace std::literals;

namespace hessian {
namespace parser {

// d x00 x00 x00 xd0 x4b x92 x84 xb8   # 9:51:31 May 8, 1998 UTC

const samples_t<date_t> samples
{
	{"d\x00\x00\x00\x00\x00\x00\x00\x00"s, date_t(boost::gregorian::date(1970, 1, 1))},
	{"d\x00\x00\x00\xd0\x4b\x92\x84\xb8"s, date_t(boost::gregorian::date(1998, 5, 8), boost::posix_time::time_duration(9, 51, 31))}
};

BOOST_AUTO_TEST_SUITE(test_date)

BOOST_DATA_TEST_CASE(test_success, samples, sample)
{
	const std::string& text = sample.first;
	date_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), date_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, sample.second);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x"s);
	date_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), date_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
