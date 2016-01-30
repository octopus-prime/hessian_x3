/*
 * int_parser.hpp
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

typedef std::int32_t int_t;

namespace parser {
namespace detail {

//int ::= 'I' b3 b2 b1 b0
//    ::= [x80-xbf]
//    ::= [xc0-xcf] b0
//    ::= [xd0-xd7] b1 b0

const auto int1_action = [](auto& ctx)
{
	const int_t b0 = x3::_attr(ctx);
	x3::_val(ctx) = b0 - 0x90;
};

const auto int2_action = [](auto& ctx)
{
	// 256 * (code - xc8) + b0
	using boost::fusion::at_c;
	const int_t b0 = at_c<1>(x3::_attr(ctx));
	const int_t b1 = at_c<0>(x3::_attr(ctx));
	x3::_val(ctx) = ((b1 - 0xc8) << 8) + b0;
};

const auto int3_action = [](auto& ctx)
{
	// 65536 * (code - xd4) + 256 * b1 + b0
	using boost::fusion::at_c;
	const int_t b0 = at_c<1>(x3::_attr(ctx));
	const int_t b1 = at_c<0>(x3::_attr(ctx));
	x3::_val(ctx) = ((b1 - 0xd4) << 16) + b0;
};

const x3::rule<class int_rule, int_t> int_rule("int");
const x3::rule<class int1_rule, int_t> int1_rule;
const x3::rule<class int2_rule, int_t> int2_rule;
const x3::rule<class int3_rule, int_t> int3_rule;
const x3::rule<class int4_rule, int_t> int4_rule;

const auto int_rule_def = int1_rule | int2_rule | int3_rule | int4_rule;
const auto int1_rule_def = byte_rule(0x80, 0xbf) [ int1_action ];
const auto int2_rule_def = (byte_rule(0xc0, 0xcf) >> x3::byte_) [ int2_action ];
const auto int3_rule_def = (byte_rule(0xd0, 0xdf) >> x3::big_word) [ int3_action ];
const auto int4_rule_def = x3::lit('I') >> x3::big_dword;

BOOST_SPIRIT_DEFINE(int_rule, int1_rule, int2_rule, int3_rule, int4_rule);

}

using detail::int_rule;

}
}
