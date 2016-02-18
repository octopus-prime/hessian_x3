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

namespace hessian {
namespace parser {

const samples_t<double_t> samples
{
	{"\x5b"s, 0.0},
	{"\x5c"s, 1.0},
	{"\x5d\x02"s, 2.0},
	{"\x5d\x7f"s, 127.0},
	{"\x5d\x80"s, -128.0},
	{"\x5e\x00\x80"s, 128.0},
	{"\x5e\xff\x7f"s, -129.0},
	{"\x5e\x7f\xff"s, 32767.0},
	{"\x5e\x80\x00"s, -32768.0},
	{"\x5f\x00\x00\x00\x01"s, 0.001},
	{"\x5f\xff\xff\xff\xff"s, -0.001},
	{"\x5f\x00\x01\x00\x00"s, 65.536},
	{"D\x40\x09\x21\xf9\xf0\x1b\x86\x6e"s, 3.14159}
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

	BOOST_CHECK(!x3::parse(text.begin(), text.end(), double_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
