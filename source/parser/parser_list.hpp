/*
 * parser_list.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {

const x3::rule<class list_rule, list_t> list_rule("list");
const x3::rule<class list1_rule, list_t> list1_rule;
const x3::rule<class list2_rule, list_t> list2_rule;
const x3::rule<class length_rule, size_t> length_rule("length");
const x3::rule<class length1_rule, size_t> length1_rule;
const x3::rule<class length2_rule, size_t> length2_rule;
const x3::rule<class length3_rule, size_t> length3_rule;
const x3::rule<class length4_rule, size_t> length4_rule;

struct list_parser : x3::parser<list_parser>
{
    using attribute_type = hessian::list_t;

    template <typename It, typename Ctx, typename Attr>
	bool parse(It& f, It const& l, Ctx&, x3::unused_type, Attr& attr) const
    {
		const auto saved = f;
		size_t len;

		if (x3::parse(f, l, length_rule, len))
			if (x3::parse(f, l, x3::repeat(len) [value_rule], attr))
				return true;

		f = saved;
		return false;
	}
};

const auto list_rule_def = list1_rule | list2_rule;
const auto list1_rule_def = x3::lit('W') >> *(value_rule - x3::lit('Z')) >> x3::lit('Z');
const auto list2_rule_def = list_parser();
const auto length_rule_def = length1_rule | length2_rule | length3_rule | length4_rule;
const auto length1_rule_def = byte_rule(0x78, 0x7f) [ calc_action<size_t,0>(0x78) ];
const auto length2_rule_def = x3::lit('X') >> int_rule;
const auto length3_rule_def = (byte_rule(0x70, 0x77) >> type_rule) [ calc_action<size_t,0>(0x70) ];
const auto length4_rule_def = x3::lit('V') >> type_rule >> int_rule;

BOOST_SPIRIT_DEFINE(list_rule, list1_rule, list2_rule, length_rule, length1_rule, length2_rule, length3_rule, length4_rule);

}
}
