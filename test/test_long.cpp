/*
 * test_long.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <long_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "sample.hpp"

using namespace std::literals;

namespace hessian {
namespace parser {

//xe0                  # 0
//xd8                  # -8
//xef                  # 15
//
//xf8 x00              # 0
//xf0 x00              # -2048
//xf7 x00              # -256
//xff xff              # 2047
//
//x3c x00 x00          # 0
//x38 x00 x00          # -262144
//x3f xff xff          # 262143
//
//x77 x00 x00 x00 x00  # 0
//x77 x00 x00 x01 x2c  # 300
//
//L x00 x00 x00 x00 x00 x00 x01 x2c  # 300

const samples_t<long_t> samples
{
	{"\xe0"s, 0},
	{"\xd8"s, -8},
	{"\xef"s, 15},

	{"\xf8\x00"s, 0},
	{"\xf0\x00"s, -2048},
	{"\xf7\x00"s, -256},
	{"\xff\xff"s, 2047},

	{"\x3c\x00\x00"s, 0},
	{"\x38\x00\x00"s, -262144},
	{"\x3f\xff\xff"s, 262143},

	{"w\x00\x00\x00\x00"s, 0},
	{"w\x00\x00\x01\x2c"s, 300},

	{"L\x00\x00\x00\x00\x00\x00\x01\x2c"s, 300}
};

BOOST_AUTO_TEST_SUITE(test_long)

BOOST_DATA_TEST_CASE(test_success, samples, sample)
{
	const std::string& text = sample.first;
	long_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), long_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, sample.second);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x");
	long_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), long_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
