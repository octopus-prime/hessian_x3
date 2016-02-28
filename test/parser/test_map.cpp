/*
 * test_map.cpp
 *
 *  Created on: 19.02.2016
 *      Author: mike_gresens
 */

#include <hessian/parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "../sample.hpp"

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

const failure_samples_t failure_samples
{
	"H"s,
	"HNZ"s,
	"HZZ"s,
	"M"s,
	"MN"s,
	"M\x00NZ"s,
	"M\x00ZZ"s
};

BOOST_AUTO_TEST_SUITE(test_map)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	content_t content;
	BOOST_REQUIRE_NO_THROW(content = parse("H\x02\x00""R"s + sample.first));
	BOOST_CHECK_EQUAL(boost::get<value_t>(content), sample.second);
}

BOOST_DATA_TEST_CASE(test_failure, failure_samples, sample)
{
	BOOST_CHECK_THROW(parse("H\x02\x00""R"s + sample), parse_exception);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
