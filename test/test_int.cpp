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

namespace hessian {
namespace parser {

const samples_t<int_t> samples
{
	{"\x90"s, 0},
	{"\x91"s, 1},
	{"\xbf"s, 47},
	{"\x80"s, -16},
	{"\xc8\x30"s, 0x30},
	{"\xcf\xff"s, 0x7ff},
	{"\xc7\xef"s, -17},
	{"\xc0\x00"s, -0x800},
	{"\xd4\x08\x00"s, 0x800},
	{"\xd7\xff\xff"s, 0x3ffff},
	{"\xd3\xf7\xff"s, -0x801},
	{"\xd0\x00\x00"s, -0x40000},
	{"I\x00\x04\x00\x00"s, 0x40000},
	{"I\x7f\xff\xff\xff"s, 0x7fffffff},
	{"I\xff\xfb\xff\xff"s, -0x40001},
	{"I\x80\x00\x00\x00"s, -0x80000000}
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

	BOOST_CHECK(!x3::parse(text.begin(), text.end(), int_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
