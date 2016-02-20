/*
 * parser_map.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/fusion/include/std_pair.hpp>

namespace hessian {
namespace parser {
namespace map {

const x3::rule<class map_rule, map_t> map_rule("map");
const x3::rule<class entries_rule, map_t> entries_rule;

const auto map_rule_def = (x3::lit('H') | (x3::lit('M') >> type_rule)) >> entries_rule;
const auto entries_rule_def = *((value_rule - x3::lit('Z')) >> value_rule) >> x3::lit('Z');

BOOST_SPIRIT_DEFINE(map_rule, entries_rule);

}

using map::map_rule;

}
}
