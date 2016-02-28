/*
 * test_list.cpp
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
	{"\x78"s, list_t{}},
	{"\x79\x01""1"s, list_t{"1"s}},
	{"\x7f\x01""1""\x01""2""\x01""3""\x01""4""\x01""5""\x01""6""\x01""7"s, list_t{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s}},

	{"W\x01""1""\x01""2""\x01""3""\x01""4""\x01""5""\x01""6""\x01""7""\x01""8Z"s, list_t{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s}}
};

BOOST_AUTO_TEST_SUITE(test_list)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	string_t call;
	BOOST_REQUIRE_NO_THROW(call = generate("test"s, {sample.second}));
	BOOST_CHECK_EQUAL(call, "H\x02\x00""C\x04""test\x91"s + sample.first);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
