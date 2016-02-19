/*
 * test_string.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <hessian/parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "sample.hpp"

namespace hessian {
namespace parser {

const samples_t<string_t> samples
{
	{"\x00"s, ""s},
	{"\x05hello"s, "hello"s},
	{"\x01\xc3\x83"s, "\u00c3"s},

	{"S\x00\x05hello"s, "hello"s},
	{"s\x00\x07hello, \x05world"s, "hello, world"s},
};

BOOST_AUTO_TEST_SUITE(test_string)

BOOST_DATA_TEST_CASE(test, samples, sample)
{
	std::istringstream stream(sample.first);
	value_t value;

	BOOST_REQUIRE_NO_THROW(value = parse(stream));
	BOOST_CHECK_EQUAL(value, value_t(sample.second));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
