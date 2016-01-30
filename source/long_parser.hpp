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

//long ::= 'L' b7 b6 b5 b4 b3 b2 b1 b0
//     ::= [xd8-xef]
//     ::= [xf0-xff] b0
//     ::= [x38-x3f] b1 b0
//     ::= x77 b3 b2 b1 b0

const auto long1_action = [](auto& ctx)
{
	// code - xe0
	const long_t b0 = x3::_attr(ctx);
	x3::_val(ctx) = b0 - 0xe0;
};

const auto long2_action = [](auto& ctx)
{
	// 256 * (code - xf8) + b0
	using boost::fusion::at_c;
	const long_t b0 = at_c<1>(x3::_attr(ctx));
	const long_t b1 = at_c<0>(x3::_attr(ctx));
	x3::_val(ctx) = ((b1 - 0xf8) << 8) + b0;
};

const auto long3_action = [](auto& ctx)
{
	// 65536 * (code - x3c) + 256 * b1 + b0
	using boost::fusion::at_c;
	const long_t b0 = at_c<1>(x3::_attr(ctx));
	const long_t b1 = at_c<0>(x3::_attr(ctx));
	x3::_val(ctx) = ((b1 - 0x3c) << 16) + b0;
};

const x3::rule<class long_rule, long_t> long_rule("long");
const x3::rule<class long1_rule, long_t> long1_rule;
const x3::rule<class long2_rule, long_t> long2_rule;
const x3::rule<class long3_rule, long_t> long3_rule;
const x3::rule<class long4_rule, long_t> long4_rule;
const x3::rule<class long5_rule, long_t> long5_rule;

const auto long_rule_def = long1_rule | long2_rule | long3_rule | long4_rule | long5_rule;

const auto long1_rule_def = byte_rule(0xd8, 0xef) [ long1_action ];
const auto long2_rule_def = (byte_rule(0xf0, 0xff) >> x3::byte_) [ long2_action ];
const auto long3_rule_def = (byte_rule(0x38, 0x3f) >> x3::big_word) [ long3_action ];
const auto long4_rule_def = x3::lit('w') >> x3::big_dword;
const auto long5_rule_def = x3::lit('L') >> x3::big_qword;

BOOST_SPIRIT_DEFINE(long_rule, long1_rule, long2_rule, long3_rule, long4_rule, long5_rule);

}

using detail::long_rule;

}
}
