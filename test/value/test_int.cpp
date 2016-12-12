/*
 * test_int.cpp
 *
 *  Created on: 12.12.2016
 *      Author: mgresens
 */

#include <hessian/value.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/lexical_cast.hpp>
#include "types.hpp"

namespace hessian {

typedef mpl::remove<all_types, int_t>::type other_types;

BOOST_AUTO_TEST_SUITE(test_int)

BOOST_AUTO_TEST_CASE(test_get_success)
{
	value_t value = int_t();
	BOOST_CHECK_NO_THROW(boost::get<int_t>(value));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_get_failure, type, other_types)
{
	value_t value = type();
	BOOST_CHECK_THROW(boost::get<int_t>(value), std::exception);
}

BOOST_AUTO_TEST_CASE(test_hash_type)
{
	value_t value = int_t();
	hash hash;
	BOOST_CHECK_EQUAL(hash(value), hash(value));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hash_types, type, other_types)
{
	value_t value = type();
	hash hash;
	BOOST_CHECK_NE(hash(int_t()), hash(value));
}

BOOST_AUTO_TEST_CASE(test_hash_values)
{
	hash hash;
	BOOST_CHECK_NE(hash(int_t(0)), hash(int_t(1)));
}

const std::initializer_list<value_t> values =
{
	int_t(0),
	int_t(1)
};

const std::initializer_list<string_t> strings =
{
	"int(0)",
	"int(1)"
};

BOOST_DATA_TEST_CASE(test_output, values ^ strings, value, string)
{
	BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(value), string);
}

BOOST_AUTO_TEST_SUITE_END()

}
