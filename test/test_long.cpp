/*
 * test_long.cpp
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

const success_samples_t success_samples
{
	{"\xe0"s, 0l},
	{"\xe1"s, 1l},
	{"\xef"s, 15l},
	{"\xd8"s, -8l},
	{"\xf8\x10"s, 0x10l},
	{"\xff\xff"s, 0x7ffl},
	{"\xf7\xf7"s, -9l},
	{"\xf0\x00"s, -0x800l},
	{"\x3c\x08\x00"s, 0x800l},
	{"\x3b\xf7\xff"s, -0x801l},
	{"\x3f\xff\xff"s, 0x3ffffl},
	{"\x38\x00\x00"s, -0x40000l},
	{"Y\x00\x04\x00\x00"s, 0x40000l},
	{"Y\xff\xfb\xff\xff"s, -0x40001l},
	{"Y\x7f\xff\xff\xff"s, 0x7fffffffl},
	{"Y\x80\x00\x00\x00"s, -0x80000000l},
	{"L\x00\x00\x00\x00\x80\x00\x00\x00"s, 0x80000000l},
	{"L\xff\xff\xff\xff\x7f\xff\xff\xff"s, -0x80000001l}
};

BOOST_AUTO_TEST_SUITE(test_long)

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
