/*
 * test_string.cpp
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

const string_t s1023 = make_string_1023();
const string_t s1024 = make_string_1024();
const string_t s65535 = make_string_65535();
const string_t s65536 = make_string_65536();

const success_samples_t success_samples
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

const failure_samples_t failure_samples
{
	"\x00 "s,
	"\x01"s,
	"\x01""12"s,
	"R\x00\x00"s
};

BOOST_AUTO_TEST_SUITE(test_string)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	content_t content;
	BOOST_REQUIRE_NO_THROW(content = parse("H\x02\x00""R"s + sample.first));
	BOOST_CHECK_EQUAL(boost::get<value_t>(content), sample.second);
}

BOOST_DATA_TEST_CASE(test_failure, failure_samples, sample)
{
	BOOST_CHECK_THROW(parse("H\x02\x00""R"s + sample), parse_exception);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
