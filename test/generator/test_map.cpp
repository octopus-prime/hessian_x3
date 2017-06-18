/*
 * test_map.cpp
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
	{"HZ"s, map_t{}},
	{"H""\x01""a""\x90""Z"s, map_t{{"a"s, 0}}},
	{"H""\x90""\x01""a""\x91""\x01""b""Z"s, map_t{{0, "a"s}, {1, "b"s}}},
	{"H""\x79""\x01""a""\x90""Z"s, map_t{{list_t{"a"s}, 0}}},
};

BOOST_AUTO_TEST_SUITE(test_map)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	string_t call;
	BOOST_REQUIRE_NO_THROW(call = generate("test"s, {sample.second}));
	BOOST_CHECK_EQUAL(call, "H\x02\x00""C\x04""test\x91"s + sample.first);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
