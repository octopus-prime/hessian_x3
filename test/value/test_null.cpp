/*
 * test_null.cpp
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

BOOST_AUTO_TEST_SUITE(test_null)

typedef null_t this_type;
typedef mpl::remove<all_types, this_type>::type other_types;

const std::initializer_list<value_t> values =
{
	this_type()
};

const std::initializer_list<string_t> strings =
{
	"null"
};

#include "test.hpp"

BOOST_AUTO_TEST_SUITE_END()

}
