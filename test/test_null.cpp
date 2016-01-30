/*
 * test_null.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <null_parser.hpp>
#include <boost/test/unit_test.hpp>

using namespace std::literals;

namespace hessian {
namespace parser {

BOOST_AUTO_TEST_SUITE(test_null)

BOOST_AUTO_TEST_CASE(test_success)
{
	const std::string text("N"s);
	null_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), null_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, null_t());
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x"s);
	null_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), null_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
