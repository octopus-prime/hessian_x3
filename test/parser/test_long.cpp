/*
 * test_long.cpp
 *
 *  Created on: 30.01.2016
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
	{"\xe0"s, 0_l},
	{"\xe1"s, 1_l},
	{"\xef"s, 15_l},
	{"\xd8"s, -8_l},
	{"\xf8\x10"s, 0x10_l},
	{"\xff\xff"s, 0x7ff_l},
	{"\xf7\xf7"s, -9_l},
	{"\xf0\x00"s, -0x800_l},
	{"\x3c\x08\x00"s, 0x800_l},
	{"\x3b\xf7\xff"s, -0x801_l},
	{"\x3f\xff\xff"s, 0x3ffff_l},
	{"\x38\x00\x00"s, -0x40000_l},
	{"Y\x00\x04\x00\x00"s, 0x40000_l},
	{"Y\xff\xfb\xff\xff"s, -0x40001_l},
	{"Y\x7f\xff\xff\xff"s, 0x7fffffff_l},
	{"Y\x80\x00\x00\x00"s, -0x80000000_l},
	{"L\x00\x00\x00\x00\x80\x00\x00\x00"s, 0x80000000_l},
	{"L\xff\xff\xff\xff\x7f\xff\xff\xff"s, -0x80000001_l}
};

BOOST_AUTO_TEST_SUITE(test_long)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	content_t content;
	BOOST_REQUIRE_NO_THROW(content = parse("H\x02\x00""R"s + sample.first));
	BOOST_CHECK_EQUAL(std::get<value_t>(content), sample.second);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
