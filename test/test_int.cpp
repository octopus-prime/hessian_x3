/*
 * test_int.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <int_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "sample.hpp"

using namespace std::literals;

namespace hessian {
namespace parser {

//		x90                # 0
//		x80                # -16
//		xbf                # 47
//
//		xc8 x00            # 0
//		xc0 x00            # -2048
//		xc7 x00            # -256
//		xcf xff            # 2047
//
//		xd4 x00 x00        # 0
//		xd0 x00 x00        # -262144
//		xd7 xff xff        # 262143
//
//		I x00 x00 x00 x00  # 0
//		I x00 x00 x01 x2c  # 300

const samples_t<int_t> samples
{
	{"\x90"s, 0},
	{"\x80"s, -16},
	{"\xbf"s, 47},

	{"\xc8\x00"s, 0},
	{"\xc0\x00"s, -2048},
	{"\xc7\x00"s, -256},
	{"\xcf\xff"s, 2047},

	{"\xd4\x00\x00"s, 0},
	{"\xd0\x00\x00"s, -262144},
	{"\xd7\xff\xff"s, 262143},

	{"I\x00\x00\x00\x00"s, 0},
	{"I\x00\x00\x01\x2c"s, 300}
};

BOOST_AUTO_TEST_SUITE(test_int)

BOOST_DATA_TEST_CASE(test_success, samples, sample)
{
	const std::string& text = sample.first;
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, sample.second);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x");
	int_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), int_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
