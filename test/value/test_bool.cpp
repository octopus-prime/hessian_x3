/*
 * test_bool.cpp
 *
 *  Created on: 12.12.2016
 *      Author: mgresens
 */

#include <hessian/value.hpp>
#include <boost/test/unit_test.hpp>
#include "types.hpp"

namespace hessian {

typedef mpl::remove<all_types, bool_t>::type other_types;

BOOST_AUTO_TEST_SUITE(test_bool)

BOOST_AUTO_TEST_CASE(test_get_success)
{
	value_t value = bool_t();
	BOOST_CHECK_NO_THROW(boost::get<bool_t>(value));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_get_failure, type, other_types)
{
	value_t value = type();
	BOOST_CHECK_THROW(boost::get<bool_t>(value), std::exception);
}

BOOST_AUTO_TEST_SUITE_END()

}
