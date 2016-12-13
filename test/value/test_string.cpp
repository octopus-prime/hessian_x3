/*
 * test_binary.cpp
 *
 *  Created on: 13.12.2016
 *      Author: mgresens
 */

#include <hessian/value.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/lexical_cast.hpp>
#include "types.hpp"
#include "../literals.hpp"

namespace hessian {

BOOST_AUTO_TEST_SUITE(test_binary)

typedef binary_t this_type;
typedef mpl::remove<all_types, this_type>::type other_types;

const std::initializer_list<value_t> values =
{
	this_type(),
	this_type("foo"_b),
	this_type("bar"_b)
};

const std::initializer_list<string_t> strings =
{
	"binary('')",
	"binary('666F6F')",
	"binary('626172')"
};

#include "test.hpp"

BOOST_AUTO_TEST_SUITE_END()

}
