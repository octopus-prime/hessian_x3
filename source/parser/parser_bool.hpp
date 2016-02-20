/*
 * parser_bool.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {
namespace bool_ {

const x3::rule<class bool_rule, bool_t> bool_rule("bool");
const x3::rule<class true_rule, bool_t> true_rule;
const x3::rule<class false_rule, bool_t> false_rule;

const auto bool_rule_def = true_rule | false_rule;
const auto true_rule_def = x3::lit('T') >> x3::attr(true);
const auto false_rule_def = x3::lit('F') >> x3::attr(false);

BOOST_SPIRIT_DEFINE(bool_rule, true_rule, false_rule);

}

using bool_::bool_rule;

}
}
