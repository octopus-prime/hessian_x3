/*
 * test_exception.cpp
 *
 *  Created on: 10.12.2016
 *      Author: mike
 */

#include <hessian/parser.hpp>
#include <boost/test/unit_test.hpp>

namespace hessian {
namespace parser {

BOOST_AUTO_TEST_SUITE(test_exception)

BOOST_AUTO_TEST_CASE(test_failure)
{
	try
	{
		parse("foo");
	}
	catch (const parse_exception& exception)
	{
		BOOST_CHECK_EQUAL(exception.what(), "Parsing failed.");
	}
}

BOOST_AUTO_TEST_SUITE_END()

}
}
