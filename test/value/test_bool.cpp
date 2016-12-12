/*
 * test_bool.cpp
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

BOOST_AUTO_TEST_CASE(test_hash_type)
{
	value_t value = bool_t();
	hash hash;
	BOOST_CHECK_EQUAL(hash(value), hash(value));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hash_types, type, other_types)
{
	value_t value = type();
	hash hash;
	BOOST_CHECK_NE(hash(bool_t()), hash(value));
}

BOOST_AUTO_TEST_CASE(test_hash_values)
{
	value_t value = bool_t(true);
	hash hash;
	BOOST_CHECK_NE(hash(bool_t(true)), hash(bool_t(false)));
}

const std::initializer_list<value_t> values =
{
	false,
	true
};

const std::initializer_list<string_t> strings =
{
	"bool(false)",
	"bool(true)"
};

BOOST_DATA_TEST_CASE(test_output, values ^ strings, value, string)
{
	BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(value), string);
}

BOOST_AUTO_TEST_SUITE_END()

}
