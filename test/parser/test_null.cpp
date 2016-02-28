/*
 * test_null.cpp
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
	{"N"s, null_t()}
};

BOOST_AUTO_TEST_SUITE(test_null)

BOOST_DATA_TEST_CASE(test_success, success_samples, sample)
{
	content_t content;
	BOOST_REQUIRE_NO_THROW(content = parse("H\x02\x00""R"s + sample.first));
	BOOST_CHECK_EQUAL(boost::get<value_t>(content), sample.second);
}

BOOST_AUTO_TEST_SUITE_END()

}
}
