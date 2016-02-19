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

const samples_t<list_t> samples
{
	{"\x78"s, {}},
	{"WTFZ"s, {true, false}},
	{"\x7aTF"s, {true, false}},
};

BOOST_AUTO_TEST_SUITE(test_list)

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
