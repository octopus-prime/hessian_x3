/*
 * test_binary.cpp
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

const string_t s1023 = make_string_1023();
const string_t s1024 = make_string_1024();
const string_t s65535 = make_string_65535();
const string_t s65536 = make_string_65536();

const success_samples_t success_samples
{
	{"\x20"s, ""_b},
	{"\x21""0"s, "0"_b},
	{"\x2f""012345678901234"s, "012345678901234"_b},
	{"\x34\x10""0123456789012345"s, "0123456789012345"_b},
	{"\x37\xff"s + s1023, binary_t(s1023.begin(), s1023.end())},
	{"B\x04\x00"s + s1024, binary_t(s1024.begin(), s1024.end())},
	{"B\xff\xff"s + s65535, binary_t(s65535.begin(), s65535.end())},
	{"A\xff\xff"s + string_t(s65536).insert(65535, 1, '\x21'), binary_t(s65536.begin(), s65536.end())}
};

BOOST_AUTO_TEST_SUITE(test_binary)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	string_t call;
	BOOST_REQUIRE_NO_THROW(call = generate("test"s, {sample.second}));
	BOOST_CHECK_EQUAL(call, "H\x02\x00""C\x04""test\x91"s + sample.first);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
