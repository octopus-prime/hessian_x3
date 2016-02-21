/*
 * parser_ref.hpp
 *
 *  Created on: 21.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {

struct ref_tag;
typedef list_t ref_t;

namespace ref {

const x3::rule<class ref_rule, value_t> ref_rule("ref");

const auto ref_action = [](auto& ctx)
{
	const ref_t& ref = x3::get<ref_tag>(ctx);
	x3::_val(ctx) = ref.at(x3::_attr(ctx));
};

const auto ref_rule_def = x3::lit('Q') >> int_rule [ ref_action ];

BOOST_SPIRIT_DEFINE(ref_rule);

}

using ref::ref_rule;

}
}
