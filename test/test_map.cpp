/*
 * test_map.cpp
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
	{"HZ"s, map_t{}},
	{"H""\x01""a""\x90""Z"s, map_t{{"a"s, 0}}},
	{"H""\x90""\x01""a""\x91""\x01""b""Z"s, map_t{{0, "a"s}, {1, "b"s}}},
	{"H""\x79""\x01""a""\x90""Z"s, map_t{{list_t{"a"s}, 0}}},

	{"M""\x13""java.lang.Hashtable""Z"s, map_t{}},
	{"M""\x13""java.lang.Hashtable""\x01""a""\x90""Z"s, map_t{{"a"s, 0}}},
	{"M""\x13""java.lang.Hashtable""\x90""\x01""a""\x91""\x01""b""Z"s, map_t{{0, "a"s}, {1, "b"s}}},
	{"M""\x13""java.lang.Hashtable""\x79""\x01""a""\x90""Z"s, map_t{{list_t{"a"s}, 0}}}
};

BOOST_AUTO_TEST_SUITE(test_map)

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
