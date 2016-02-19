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

struct list_parser : x3::parser<list_parser>
{
    using attribute_type = hessian::list_t;

    template <typename It, typename Ctx, typename Attr>
	bool parse(It& f, It const& l, Ctx&, x3::unused_type, Attr& attr) const
    {
		const auto saved = f;
		size_t len;

		if (x3::parse(f,l,length_rule,len))
		{
			size_t i = 0;

			for (; i < len; ++i)
			{
				value_t val;

				if (!x3::parse(f, l, value_rule, val))
					break;

				attr.push_back(val);
			}

			return len == i;
		}

		f = saved;
		return false;
	}
};

const auto list_action = [](auto& ctx)
{
	const size_t length = x3::_attr(ctx);
	list_t list;

	auto begin = x3::_where(ctx).begin();
	auto end = x3::_where(ctx).end();

	std::cout << length << std::endl;
	for (size_t i = 0; i < length; ++i)
	{
		std::cout << i << std::endl;
		value_t value;
		x3::parse(begin, end, value_rule, value);
		list.push_back(value);
	}

	x3::_val(ctx) = std::move(list);
};

const auto list_rule_def = list1_rule | list2_rule;
const auto list1_rule_def = x3::lit('W') >> *(value_rule - x3::lit('Z')) >> x3::lit('Z');
//const auto list2_rule_def = list_parser();
const auto list2_rule_def = length_rule [ list_action ];
const auto length_rule_def = length1_rule | length2_rule;
const auto length1_rule_def = byte_rule(0x78, 0x7f) [ calc_action<size_t,0>(0x78) ];
const auto length2_rule_def = x3::lit('X') >> int_rule;

BOOST_SPIRIT_DEFINE(list_rule, list1_rule, list2_rule, length_rule, length1_rule, length2_rule);

}
}
