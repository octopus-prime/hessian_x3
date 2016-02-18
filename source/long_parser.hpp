/*
 * long_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/binary.hpp>
#include <cstdint>
#include "byte_parser.hpp"

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef std::int64_t long_t;

namespace parser {
namespace detail {

const x3::rule<class long_rule, long_t> long_rule("long");
const x3::rule<class long1_rule, long_t> long1_rule;
const x3::rule<class long2_rule, long_t> long2_rule;
const x3::rule<class long3_rule, long_t> long3_rule;
const x3::rule<class long4_rule, std::int32_t> long4_rule;
const x3::rule<class long5_rule, long_t> long5_rule;

const auto long_rule_def = long1_rule | long2_rule | long3_rule | long4_rule | long5_rule;

const auto long1_rule_def = byte_rule(0xd8, 0xef) [ calc_action<long_t,0>(0xe0) ];
const auto long2_rule_def = (byte_rule(0xf0, 0xff) >> x3::byte_) [ calc_action<long_t,8>(0xf8) ];
const auto long3_rule_def = (byte_rule(0x38, 0x3f) >> x3::big_word) [ calc_action<long_t,16>(0x3c) ];
const auto long4_rule_def = x3::lit('Y') >> x3::big_dword;
const auto long5_rule_def = x3::lit('L') >> x3::big_qword;

BOOST_SPIRIT_DEFINE(long_rule, long1_rule, long2_rule, long3_rule, long4_rule, long5_rule);

}

using detail::long_rule;

}
}
