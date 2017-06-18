/*
 * test.hpp
 *
 *  Created on: 13.12.2016
 *      Author: mgresens
 */

#pragma once

const auto default_value = *values.begin();
const auto other_values = boost::make_iterator_range(values.begin() + 1, values.end());

BOOST_AUTO_TEST_SUITE(test_get)

BOOST_AUTO_TEST_CASE(test_same)
{
	BOOST_CHECK_NO_THROW(default_value.as<this_type>());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_other_type, other_type, other_types)
{
	const value_t other_value = other_type();
	BOOST_CHECK_THROW(other_value.as<this_type>(), std::exception);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_equals)

BOOST_AUTO_TEST_CASE(test_same)
{
	BOOST_CHECK_EQUAL(default_value, default_value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_other_type, other_type, other_types)
{
	const value_t other_value = other_type();
	BOOST_CHECK_NE(default_value, other_value);
}

BOOST_DATA_TEST_CASE(test_other_value, other_values, other_value)
{
	BOOST_CHECK_NE(default_value, other_value);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_DATA_TEST_CASE(test_output, values ^ strings, value, string)
{
	BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(value), string);
}
