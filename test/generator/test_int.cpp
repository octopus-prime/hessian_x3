/*
 * test_int.cpp
 *
 *  Created on: 28.02.2016
 *      Author: mike_gresens
 */

#include <hessian/generator.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "../sample.hpp"

namespace hessian {
namespace generator {

const success_samples_t success_samples
{
	{"\x90"s, 0_i},
	{"\x91"s, 1_i},
	{"\xbf"s, 47_i},
	{"\x80"s, -16_i},
	{"\xc8\x30"s, 0x30_i},
	{"\xcf\xff"s, 0x7ff_i},
	{"\xc7\xef"s, -17_i},
	{"\xc0\x00"s, -0x800_i},
	{"\xd4\x08\x00"s, 0x800_i},
	{"\xd7\xff\xff"s, 0x3ffff_i},
	{"\xd3\xf7\xff"s, -0x801_i},
	{"\xd0\x00\x00"s, -0x40000_i},
	{"I\x00\x04\x00\x00"s, 0x40000_i},
	{"I\x7f\xff\xff\xff"s, 0x7fffffff_i},
	{"I\xff\xfb\xff\xff"s, -0x40001_i},
	{"I\x80\x00\x00\x00"s, -0x80000000_i}
};

BOOST_AUTO_TEST_SUITE(test_int)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	string_t call;
	BOOST_REQUIRE_NO_THROW(call = generate("test"s, {sample.second}));
	BOOST_CHECK_EQUAL(call, "H\x02\x00""C\x04""test\x91"s + sample.first);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
