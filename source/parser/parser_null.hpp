/*
 * parser_null.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {
namespace null {

const x3::rule<class null_rule, null_t> null_rule("null");

const auto null_rule_def = x3::lit('N') >> x3::attr(null_t());

BOOST_SPIRIT_DEFINE(null_rule);

}

using null::null_rule;

}
}
