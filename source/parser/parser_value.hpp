/*
 * parser_value.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {

const auto value_rule_def = null_rule | bool_rule | int_rule | long_rule | double_rule | date_rule | string_rule | binary_rule | list_rule | map_rule | object_rule | def_rule | ref_rule;

BOOST_SPIRIT_DEFINE(value_rule);

}
}
