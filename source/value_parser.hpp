/*
 * value_parser.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/variant.hpp>
#include <vector>
#include <iostream>
#include "bool_parser.hpp"
#include "date_parser.hpp"
#include "double_parser.hpp"
#include "int_parser.hpp"
#include "long_parser.hpp"
#include "null_parser.hpp"
#include "string_parser.hpp"
#include "byte_parser.hpp"

namespace x3 = boost::spirit::x3;

namespace hessian {

using x3::ascii::lit;

typedef boost::make_recursive_variant
<
	null_t,
	bool_t,
	int_t,
	long_t,
	double_t,
	date_t,
	string_t,
//	binary_t,
	std::vector<boost::recursive_variant_>									// list_t
//	std::map<boost::recursive_variant_, boost::recursive_variant_, less>,	// map_t
//	boost::unordered_map<string_t, boost::recursive_variant_>				// object_t
>::type value_t;

typedef std::vector<value_t> list_t;

}

namespace std {

inline ostream&
operator<<(ostream& stream, const hessian::list_t& list)
{
	for (const hessian::value_t& value : list)
		std::cout << value << ", ";
	return stream;
}

}

namespace hessian {
namespace parser {
namespace detail {

const x3::rule<class value_rule, value_t> value_rule("value");
const x3::rule<class list_rule, list_t> list_rule("list");
const x3::rule<class list1_rule, list_t> list1_rule;
const x3::rule<class list2_rule, list_t> list2_rule;
const x3::rule<class length_rule, size_t> length_rule("length");
const x3::rule<class length1_rule, size_t> length1_rule;
const x3::rule<class length2_rule, size_t> length2_rule;

const auto value_rule_def = null_rule | bool_rule | int_rule | long_rule | double1_rule | date_rule | string_rule | list_rule;
const auto list_rule_def = list1_rule | list2_rule;
const auto list1_rule_def = x3::lit('W') >> *(value_rule - x3::lit('Z')) >> x3::lit('Z');
const auto list2_rule_def = x3::omit [length_rule] >> x3::attr(list_t());
const auto length_rule_def = length1_rule | length2_rule;
const auto length1_rule_def = byte_rule(0x78, 0x7f) [ calc_action<size_t,0>(0x78) ];
const auto length2_rule_def = x3::lit('X') >> int_rule;

BOOST_SPIRIT_DEFINE(value_rule, list_rule, list1_rule, list2_rule, length_rule, length1_rule, length2_rule);

}

using detail::value_rule;

}
}
