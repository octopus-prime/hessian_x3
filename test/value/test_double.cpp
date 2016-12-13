/*
 * test_double.cpp
 *
 *  Created on: 13.12.2016
 *      Author: mgresens
 */

#include <hessian/value.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/lexical_cast.hpp>
#include "types.hpp"

namespace hessian {

BOOST_AUTO_TEST_SUITE(test_double)

typedef double_t this_type;
typedef mpl::remove<all_types, this_type>::type other_types;

const std::initializer_list<value_t> values =
{
	this_type(0),
	this_type(1),
	this_type(-1)
};

const std::initializer_list<string_t> strings =
{
	"double(0)",
	"double(1)",
	"double(-1)"
};

#include "test.hpp"

BOOST_AUTO_TEST_SUITE_END()

}
