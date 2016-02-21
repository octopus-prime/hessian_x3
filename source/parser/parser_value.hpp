/*
 * parser_value.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace hessian {
namespace parser {

const x3::rule<class value_rule, value_t> value_rule("value");

}
}

#include "parser_byte.hpp"
#include "parser_null.hpp"
#include "parser_bool.hpp"
#include "parser_int.hpp"
#include "parser_long.hpp"
#include "parser_double.hpp"
#include "parser_date.hpp"
#include "parser_string.hpp"
#include "parser_binary.hpp"
#include "parser_type.hpp"
#include "parser_def.hpp"
#include "parser_ref.hpp"
#include "parser_list.hpp"
#include "parser_map.hpp"
#include "parser_object.hpp"

namespace hessian {
namespace parser {

const auto value_rule_def = null_rule | bool_rule | int_rule | long_rule | double_rule | date_rule | string_rule | binary_rule | list_rule | map_rule | object_rule | def_rule | ref_rule;

BOOST_SPIRIT_DEFINE(value_rule);

}
}
