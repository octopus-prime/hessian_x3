/*
 * parser_type.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {

const x3::rule<class type_rule> type_rule;

const auto type_rule_def = x3::omit [ int_rule | string_rule ];

BOOST_SPIRIT_DEFINE(type_rule);

}
}
