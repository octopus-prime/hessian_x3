/*
 * test_string.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <string_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "sample.hpp"

using namespace std::literals;

namespace hessian {
namespace parser {

//x00               # "", empty string
//x05 hello         # "hello"
//x01 xc3 x83       # "\u00c3"
//
//S x00 x05 hello   # "hello" in long form
//
//s x00 x07 hello,  # "hello, world" split into two chunks
//  x05 world

const samples_t<string_t> samples
{
	{"\x00"s, ""s},
	{"\x05hello"s, "hello"s},
	{"\x01\xc3\x83"s, "\u00c3"s},

	{"S\x00\x05hello"s, "hello"s},
	{"s\x00\x07hello, \x05world"s, "hello, world"s},
};

BOOST_AUTO_TEST_SUITE(test_string)

BOOST_DATA_TEST_CASE(test_success, samples, sample)
{
	const std::string& text = sample.first;
	string_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), string_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, sample.second);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x"s);
	string_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), string_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
