/*
 * test_list.cpp
 *
 *  Created on: 19.02.2016
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
	{"\x78"s, list_t{}},
	{"\x79\x01""1"s, list_t{"1"s}},
	{"\x7f\x01""1""\x01""2""\x01""3""\x01""4""\x01""5""\x01""6""\x01""7"s, list_t{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s}},
	{"X\x98\x01""1""\x01""2""\x01""3""\x01""4""\x01""5""\x01""6""\x01""7""\x01""8"s, list_t{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s}},

	{"\x70\x07""[string"s, list_t{}},
	{"\x71\x07""[string""\x01""1"s, list_t{"1"s}},
	{"\x77\x07""[string""\x01""1""\x01""2""\x01""3""\x01""4""\x01""5""\x01""6""\x01""7"s, list_t{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s}},
	{"V\x07[string\x98\x01""1""\x01""2""\x01""3""\x01""4""\x01""5""\x01""6""\x01""7""\x01""8"s, list_t{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s}},

	{"WZ"s, list_t{}},
	{"W\x01""1Z"s, list_t{"1"s}}
};

BOOST_AUTO_TEST_SUITE(test_list)

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
