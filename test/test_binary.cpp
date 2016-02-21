/*
 * test_binary.cpp
 *
 *  Created on: 20.02.2016
 *      Author: mike_gresens
 */

#include <hessian/parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "sample.hpp"

namespace hessian {
namespace parser {

binary_t operator"" _b(const char* s, const size_t l)
{
    return binary_t(s, s + l);
}

const string_t s1023 = make_string_1023();
const string_t s1024 = make_string_1024();
const string_t s65535 = make_string_65535();
const string_t s65536 = make_string_65536();

const samples_t samples
{
	{"\x20"s, ""_b},
	{"\x21""0"s, "0"_b},
	{"\x2f""012345678901234"s, "012345678901234"_b},
	{"\x34\x10""0123456789012345"s, "0123456789012345"_b},
	{"\x37\xff"s + s1023, binary_t(s1023.begin(), s1023.end())},
	{"B\x04\x00"s + s1024, binary_t(s1024.begin(), s1024.end())},
	{"A\x80\x00"s + string_t(s65535).insert(32768, "B\x7f\xff"s), binary_t(s65535.begin(), s65535.end())},
	{"A\xff\xff"s + string_t(s65536).insert(65535, 1, '\x21'), binary_t(s65536.begin(), s65536.end())}
};

BOOST_AUTO_TEST_SUITE(test_binary)

BOOST_DATA_TEST_CASE(test, samples, sample)
{
	std::istringstream stream(sample.first);
	value_t value;

	BOOST_REQUIRE_NO_THROW(value = parse(stream));
	BOOST_CHECK_EQUAL(value, sample.second);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
