/*
 * test_object.cpp
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
	{"C""\x00""\x90""\x60"s, object_t{}},
	{"C""\x00""\x91""\x06""_value""\x60""\x90"s, object_t{{"_value"s, 0}}},
	{"\x7a""C""\x00""\x91""\x06""_value""\x60""\x90""\x60""\x91"s, list_t{object_t{{"_value"s, 0}},object_t{{"_value"s, 1}}}},
	{"\x7a""C""\x00""\x91""\x06""_value""\x60""\x90""Q""\x91"s, list_t{object_t{{"_value"s, 0}},object_t{{"_value"s, 0}}}}
};

BOOST_AUTO_TEST_SUITE(test_object)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	string_t call;
	BOOST_REQUIRE_NO_THROW(call = generate("test"s, {sample.second}));
	BOOST_CHECK_EQUAL(call, "H\x02\x00""C\x04""test\x91"s + sample.first);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
