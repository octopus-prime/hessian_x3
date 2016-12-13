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

BOOST_AUTO_TEST_SUITE(test_bool)

typedef bool_t this_type;
typedef mpl::remove<all_types, this_type>::type other_types;

const std::initializer_list<value_t> values =
{
	this_type(false),
	this_type(true)
};

const std::initializer_list<string_t> strings =
{
	"bool(false)",
	"bool(true)"
};

#include "test.hpp"

BOOST_AUTO_TEST_SUITE_END()

}
