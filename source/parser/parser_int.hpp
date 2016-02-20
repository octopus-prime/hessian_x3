/*
 * parser_int.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {
namespace int_ {

const x3::rule<class int_rule, int_t> int_rule("int");
const x3::rule<class int1_rule, int_t> int1_rule;
const x3::rule<class int2_rule, int_t> int2_rule;
const x3::rule<class int3_rule, int_t> int3_rule;
const x3::rule<class int4_rule, int_t> int4_rule;

const auto int_rule_def = int1_rule | int2_rule | int3_rule | int4_rule;
const auto int1_rule_def = byte_rule(0x80, 0xbf) [ calc_action<int_t,0>(0x90) ];
const auto int2_rule_def = (byte_rule(0xc0, 0xcf) >> x3::byte_) [ calc_action<int_t,8>(0xc8) ];
const auto int3_rule_def = (byte_rule(0xd0, 0xdf) >> x3::big_word) [ calc_action<int_t,16>(0xd4) ];
const auto int4_rule_def = x3::lit('I') >> x3::big_dword;

BOOST_SPIRIT_DEFINE(int_rule, int1_rule, int2_rule, int3_rule, int4_rule);

}

using int_::int_rule;

}
}
