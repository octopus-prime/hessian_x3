/*
 * test_null.cpp
 *
 *  Created on: 12.12.2016
 *      Author: mgresens
 */

#include <hessian/value.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include "types.hpp"

namespace hessian {

typedef mpl::remove<all_types, null_t>::type other_types;

BOOST_AUTO_TEST_SUITE(test_null)

BOOST_AUTO_TEST_CASE(test_get_success)
{
	value_t value = null_t();
	BOOST_CHECK_NO_THROW(boost::get<null_t>(value));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_get_failure, type, other_types)
{
	value_t value = type();
	BOOST_CHECK_THROW(boost::get<null_t>(value), std::exception);
}

BOOST_AUTO_TEST_CASE(test_hash_equal)
{
	value_t value = null_t();
	hash hash;
	BOOST_CHECK_EQUAL(hash(value), hash(value));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hash_types, type, other_types)
{
	value_t value = type();
	hash hash;
	BOOST_CHECK_NE(hash(null_t()), hash(value));
}

BOOST_AUTO_TEST_CASE(test_output)
{
	value_t value = null_t();
	BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(value), "null");
}

BOOST_AUTO_TEST_SUITE_END()

}
