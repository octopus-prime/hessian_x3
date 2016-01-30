/*
 * int_test.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <int_parser.hpp>
#include <boost/test/unit_test.hpp>

using namespace std::literals;

namespace hessian {
namespace parser {

BOOST_AUTO_TEST_SUITE(test_parser_int)

//		x90                # 0
//		x80                # -16
//		xbf                # 47
//
//		xc8 x00            # 0
//		xc0 x00            # -2048
//		xc7 x00            # -256
//		xcf xff            # 2047
//
//		xd4 x00 x00        # 0
//		xd0 x00 x00        # -262144
//		xd7 xff xff        # 262143
//
//		I x00 x00 x00 x00  # 0
//		I x00 x00 x01 x2c  # 300

BOOST_AUTO_TEST_CASE(test_int1_0)
{
	const std::string text("\x90"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 0);
}

BOOST_AUTO_TEST_CASE(test_int1_16)
{
	const std::string text("\x80"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, -16);
}

BOOST_AUTO_TEST_CASE(test_int1_47)
{
	const std::string text("\xbf"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 47);
}

BOOST_AUTO_TEST_CASE(test_int2_0)
{
	const std::string text("\xc8\x00"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 0);
}

BOOST_AUTO_TEST_CASE(test_int2_2048)
{
	const std::string text("\xc0\x00"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, -2048);
}

BOOST_AUTO_TEST_CASE(test_int2_256)
{
	const std::string text("\xc7\x00"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, -256);
}

BOOST_AUTO_TEST_CASE(test_int2_2047)
{
	const std::string text("\xcf\xff"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 2047);
}

BOOST_AUTO_TEST_CASE(test_int3_0)
{
	const std::string text("\xd4\x00\x00"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 0);
}

BOOST_AUTO_TEST_CASE(test_int3_262144)
{
	const std::string text("\xd0\x00\x00"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, -262144);
}

BOOST_AUTO_TEST_CASE(test_int3_262143)
{
	const std::string text("\xd7\xff\xff"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 262143);
}

BOOST_AUTO_TEST_CASE(test_int4_0)
{
	const std::string text("I\x00\x00\x00\x00"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 0);
}

BOOST_AUTO_TEST_CASE(test_int4_300)
{
	const std::string text("I\x00\x00\x01\x2c"s);
	int_t attr;
	auto iter = text.begin();

	BOOST_REQUIRE(x3::parse(iter, text.end(), int_rule, attr));
	BOOST_REQUIRE(iter == text.end());
	BOOST_CHECK_EQUAL(attr, 300);
}

BOOST_AUTO_TEST_CASE(test_failure)
{
	const std::string text("x");
	int_t attr;
	auto iter = text.begin();

	BOOST_CHECK(!x3::parse(iter, text.end(), int_rule, attr));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
