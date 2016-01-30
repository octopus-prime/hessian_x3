/*
 * bool_test.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <bool_parser.hpp>
#include <boost/test/unit_test.hpp>

namespace hessian {
namespace parser {

BOOST_AUTO_TEST_SUITE(test_parser_bool)

BOOST_AUTO_TEST_CASE(test_true)
{
	const std::string text("T");
	bool_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), bool_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, true);
}

BOOST_AUTO_TEST_CASE(test_false)
{
	const std::string text("F");
	bool_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), bool_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, false);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x");
	bool_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), bool_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
