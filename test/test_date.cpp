/*
 * test_date.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <date_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/date_time.hpp>
#include "sample.hpp"

using boost::posix_time::from_iso_string;

namespace hessian {
namespace parser {

const samples_t<date_t> samples
{
	{"K\x00\x00\x00\x00"s, from_iso_string("19700101T000000"s)},
	{"K\x00\xe3\x83\x8f"s, from_iso_string("19980508T095100"s)},
	{"J\x00\x00\x00\xd0\x4b\x92\x84\xb8"s, from_iso_string("19980508T095131"s)}
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

	BOOST_CHECK(!x3::parse(text.begin(), text.end(), date_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
