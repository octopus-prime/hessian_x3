/*
 * parser_object.hpp
 *
 *  Created on: 20.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/fusion/adapted/std_tuple.hpp>

namespace hessian {
namespace parser {
namespace object {

const x3::rule<class object_rule, object_t> object_rule("object");
const x3::rule<class index_rule, size_t> index_rule;
const x3::rule<class index1_rule, size_t> index1_rule;
const x3::rule<class index2_rule, size_t> index2_rule;

struct object_parser : x3::parser<object_parser>
{
    using attribute_type = object_t;

    template <typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator& first, const Iterator& last, const Context& context, RContext& rcontext, Attribute& attr) const
    {
		const auto saved = first;
		size_t index = 0;

		if (index_rule.parse(first, last, context, rcontext, index))
		{
			const def_t& def = x3::get<def_tag>(context);

			for (const string_t& key : def.at(index))
			{
				value_t value;

				if (!value_rule.parse(first, last, context, rcontext, value))
					break;

				x3::traits::push_back(attr, std::make_pair(key, value));
			}

			return true;
		}

		first = saved;
		return false;
	}
};

const auto object_rule_def = object_parser();
const auto index_rule_def = index1_rule | index2_rule;
const auto index1_rule_def = byte_rule(0x60, 0x6f) [ calc_action<size_t,0>(0x60) ];
const auto index2_rule_def = x3::lit('O') >> int_rule;

BOOST_SPIRIT_DEFINE(object_rule, index_rule, index1_rule, index2_rule);

}

using object::object_rule;

}
}
