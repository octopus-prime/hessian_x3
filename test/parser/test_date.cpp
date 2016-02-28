/*
 * test_date.cpp
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

const success_samples_t success_samples
{
	{"K\x00\x00\x00\x00"s, "19700101T000000"_d},
	{"K\x00\xe3\x83\x8f"s, "19980508T095100"_d},
	{"J\x00\x00\x00\xd0\x4b\x92\x84\xb8"s, "19980508T095131"_d}
};

BOOST_AUTO_TEST_SUITE(test_date)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	content_t content;
	BOOST_REQUIRE_NO_THROW(content = parse("H\x02\x00""R"s + sample.first));
	BOOST_CHECK_EQUAL(boost::get<value_t>(content), sample.second);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
