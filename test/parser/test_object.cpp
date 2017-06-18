/*
 * test_object.cpp
 *
 *  Created on: 19.02.2016
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
	{"C""\x00""\x90""\x60"s, object_t{}},
	{"C""\x00""\x91""\x06""_value""\x60""\x90"s, object_t{{"_value"s, 0}}},
	{"\x7a""C""\x00""\x91""\x06""_value""\x60""\x90""\x60""\x91"s, list_t{object_t{{"_value"s, 0}},object_t{{"_value"s, 1}}}},
	{"\x7a""C""\x00""\x91""\x06""_value""\x60""\x90""Q""\x91"s, list_t{object_t{{"_value"s, 0}},object_t{{"_value"s, 0}}}},
	{"\x7a""C""\x00""\x91""\x06""_value""\x60""\x90""\x60""\x90"s, list_t{object_t{{"_value"s, 0}},object_t{{"_value"s, 0}}}},
	{"X""\xa1"
			"C""\x00""\x90""\x60"
			"C""\x00""\x90""\x61"
			"C""\x00""\x90""\x62"
			"C""\x00""\x90""\x63"
			"C""\x00""\x90""\x64"
			"C""\x00""\x90""\x65"
			"C""\x00""\x90""\x66"
			"C""\x00""\x90""\x67"
			"C""\x00""\x90""\x68"
			"C""\x00""\x90""\x69"
			"C""\x00""\x90""\x6a"
			"C""\x00""\x90""\x6b"
			"C""\x00""\x90""\x6c"
			"C""\x00""\x90""\x6d"
			"C""\x00""\x90""\x6e"
			"C""\x00""\x90""\x6f"
			"C""\x00""\x90""O""\xa0"s,
			list_t(17, object_t())
	}
};

BOOST_AUTO_TEST_SUITE(test_object)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	content_t content;
	BOOST_REQUIRE_NO_THROW(content = parse("H\x02\x00""R"s + sample.first));
	BOOST_CHECK_EQUAL(std::get<value_t>(content), sample.second);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
