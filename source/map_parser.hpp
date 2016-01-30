/*
 * map_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <unordered_map>

namespace x3 = boost::spirit::x3;

namespace hessian {

template <typename K, typename V>
using map_t = std::unordered_map<K, V>;

namespace parser {
namespace detail {

//map ::= M type? (value value)* z

const auto map_rule = [](const auto& key_rule, const auto& value_rule)
{
	//TODO: How to provide rule name here?!
	//TODO: Finish grammar
	const auto pair_rule = key_rule >> value_rule;
	return x3::lit('M') >> *(pair_rule - x3::lit('z')) >> x3::lit('z');
};

}

using detail::map_rule;

}
}
