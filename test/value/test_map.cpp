/*
 * test_map.cpp
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

BOOST_AUTO_TEST_SUITE(test_map)

typedef map_t this_type;
typedef mpl::remove<all_types, this_type>::type other_types;

const std::initializer_list<value_t> values =
{
	this_type(),
	this_type{{null_t(), null_t()}},
	this_type{{bool_t(true), null_t()}, {bool_t(false), null_t()}}
};

const std::initializer_list<string_t> strings =
{
	"map()",
	"map(null = null)",
#ifndef _LIBCPP_VERSION
	"map(bool(false) = null, bool(true) = null)"
#else
	"map(bool(true) = null, bool(false) = null)"
#endif
};

#include "test.hpp"

BOOST_AUTO_TEST_SUITE_END()

}
