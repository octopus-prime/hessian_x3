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

const samples_t<map_t> samples
{
	{"HZ"s, {}},
	{"H""\x01""a""\x90""Z"s, {{"a"s, 0}}},
	{"H""\x90""\x01""a""\x91""\x01""b""Z"s, {{0, "a"s}, {1, "b"s}}},
	{"H""\x79""\x01""a""\x90""Z"s, {{list_t{"a"s}, 0}}},

	{"M""\x13""java.lang.Hashtable""Z"s, {}},
	{"M""\x13""java.lang.Hashtable""\x01""a""\x90""Z"s, {{"a"s, 0}}},
	{"M""\x13""java.lang.Hashtable""\x90""\x01""a""\x91""\x01""b""Z"s, {{0, "a"s}, {1, "b"s}}},
	{"M""\x13""java.lang.Hashtable""\x79""\x01""a""\x90""Z"s, {{list_t{"a"s}, 0}}}
};

BOOST_AUTO_TEST_SUITE(test_map)

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
