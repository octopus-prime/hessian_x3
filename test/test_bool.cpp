/*
 * test_bool.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <bool_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "sample.hpp"

using namespace std::literals;

namespace hessian {
namespace parser {

//T   # true
//F   # false

const samples_t<bool_t> samples
{
	{"T"s, true},
	{"F"s, false}
};

BOOST_AUTO_TEST_SUITE(test_bool)

BOOST_DATA_TEST_CASE(test_success, samples, sample)
{
	const std::string& text = sample.first;
	bool_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), bool_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, sample.second);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x"s);
	bool_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), bool_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
