/*
 * test_string.cpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#include <hessian/parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "sample.hpp"

namespace hessian {
namespace parser {

static string_t
make_string_1024()
{
	boost::format f("%02d 456789012345678901234567890123456789012345678901234567890123\n");

	string_t value;
	for (std::size_t i = 0; i < 16; i++)
		value += (f % i).str();
	return value;
}

static string_t
make_string_1023()
{
	return boost::algorithm::erase_tail_copy(make_string_1024(), 1);
}

static string_t
make_string_65536()
{
	boost::format f("%03d 56789012345678901234567890123456789012345678901234567890123\n");

	string_t value;
	for (std::size_t j = 0; j < 2; j++)
		for (std::size_t i = 0; i < 32 * 16; i++)
			value += (f % i).str();
	return value;
}

static string_t
make_string_65535()
{
	return boost::algorithm::erase_tail_copy(make_string_65536(), 1);
}

const string_t s1023 = make_string_1023();
const string_t s1024 = make_string_1024();
const string_t s65535 = make_string_65535();
const string_t s65536 = make_string_65536();

const samples_t<string_t> samples
{
	{"\x00"s, ""s},
	{"\x01""0"s, "0"s},
	{"\x1f""0123456789012345678901234567890"s, "0123456789012345678901234567890"s},
	{"\x30\x20""01234567890123456789012345678901"s, "01234567890123456789012345678901"s},
	{"\x33\xff"s + s1023, s1023},
	{"S\x04\x00"s + s1024, s1024},
	{"R\x80\x00"s + string_t(s65535).insert(32768, "S\x7f\xff"s), s65535},
	{"R\xff\xff"s + string_t(s65536).insert(65535, 1, '\x01'), s65536},

	{"\x01\xc3\x83"s, "\u00c3"s},
	{"\x05""a""1""是""本""文"s, "a""1""是""本""文"s}
};

BOOST_AUTO_TEST_SUITE(test_string)

BOOST_DATA_TEST_CASE(test, samples, sample)
{
	std::istringstream stream(sample.first);
	value_t value;

	BOOST_REQUIRE_NO_THROW(value = parse(stream));
	BOOST_CHECK_EQUAL(value, value_t(sample.second));
}

BOOST_AUTO_TEST_SUITE_END()

}
}
