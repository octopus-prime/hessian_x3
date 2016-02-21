/*
 * test_object.cpp
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

const samples_t samples
{
	{"C""\x00""\x90""\x60"s, object_t{}},
	{"C""\x00""\x91""\x06""_value""\x60""\x90"s, object_t{{"_value"s, 0}}},
	{"\x7a""C""\x00""\x91""\x06""_value""\x60""\x90""\x60""\x91"s, list_t{object_t{{"_value"s, 0}},object_t{{"_value"s, 1}}}},
};

BOOST_AUTO_TEST_SUITE(test_object)

BOOST_DATA_TEST_CASE(test, samples, sample)
{
	std::istringstream stream(sample.first);
	value_t value;

	BOOST_REQUIRE_NO_THROW(value = parse(stream));
	BOOST_CHECK_EQUAL(value, sample.second);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
