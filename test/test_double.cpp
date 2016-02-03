/*
 * test_double.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <double_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "sample.hpp"

using namespace std::literals;

namespace hessian {
namespace parser {

//x67          # 0.0
//x68          # 1.0
//
//x69 x00      # 0.0
//x69 x80      # -128.0
//x69 xff      # 127.0
//
//x70 x00 x00  # 0.0
//x70 x80 x00  # -32768.0
//x70 xff xff  # 32767.0
//
//D x40 x28 x80 x00 x00 x00 x00 x00  # 12.25

const samples_t<double_t> samples
{
	{"\x67"s, 0.0},
	{"\x68"s, 1.0},

//	{"\x69\x00"s, 0.0},
//	{"\x69\x80"s, -128.0},
//	{"\x69\xff"s, 127.0},
//
//	{"\x70\x00\x00"s, 0.0},
//	{"\x70\x80\x00"s, -32768.0},
//	{"\x70\xff\xff"s, 32767.0},

//	{"D\x40\x28\x80\x00\x00\x00\x00\x00"s, 12.25}
};

BOOST_AUTO_TEST_SUITE(test_double)

BOOST_DATA_TEST_CASE(test_success, samples, sample)
{
	const std::string& text = sample.first;
	double_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), double_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, sample.second);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x");
	double_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), double_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
