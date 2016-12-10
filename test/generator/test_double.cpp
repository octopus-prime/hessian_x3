/*
 * test_double.cpp
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
	{"\x5b"s, 0.0},
	{"\x5c"s, 1.0},
	{"\x5d\x02"s, 2.0},
	{"\x5d\x7f"s, 127.0},
	{"\x5d\x80"s, -128.0},
	{"\x5e\x00\x80"s, 128.0},
	{"\x5e\xff\x7f"s, -129.0},
	{"\x5e\x7f\xff"s, 32767.0},
	{"\x5e\x80\x00"s, -32768.0},
	{"D\x41\x13\x2c\xbc\x00\x00\x00\x00"s, 314159.0},
	{"\x5f\x00\x00\x00\x01"s, 0.001},
	{"\x5f\xff\xff\xff\xff"s, -0.001},
	{"\x5f\x00\x01\x00\x00"s, 65.536},
	{"D\x40\x09\x21\xf9\xf0\x1b\x86\x6e"s, 3.14159}
};

BOOST_AUTO_TEST_SUITE(test_double)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	string_t call;
	BOOST_REQUIRE_NO_THROW(call = generate("test"s, {sample.second}));
	BOOST_CHECK_EQUAL(call, "H\x02\x00""C\x04""test\x91"s + sample.first);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
