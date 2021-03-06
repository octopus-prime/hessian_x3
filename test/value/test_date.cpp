/*
 * test_date.cpp
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

BOOST_AUTO_TEST_SUITE(test_date)

typedef date_t this_type;
typedef mpl::remove<all_types, this_type>::type other_types;

const std::initializer_list<value_t> values =
{
	this_type(),
	this_type("19700101T000000"_d),
	this_type("20161213T123456"_d)
};

const std::initializer_list<string_t> strings =
{
	"date(not-a-date-time)",
	"date(1970-01-01T00:00:00)",
	"date(2016-12-13T12:34:56)"
};

#include "test.hpp"

BOOST_AUTO_TEST_SUITE_END()

}
