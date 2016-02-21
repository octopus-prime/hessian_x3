/*
 * parser_map.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/fusion/include/std_pair.hpp>

namespace hessian {
namespace parser {
namespace map {

const x3::rule<class map_rule, map_t> map_rule("map");
const x3::rule<class entries_rule, map_t> entries_rule;

struct map_parser : x3::parser<map_parser>
{
    using attribute_type = map_t;

    template <typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator& first, const Iterator& last, const Context& context, RContext& rcontext, Attribute& attr) const
    {
		const auto saved = first;

		const auto rule = x3::lit('H') | (x3::lit('M') >> type_rule);
		if (x3::parse(first, last, rule))
		{
			ref_t& ref = x3::get<ref_tag>(context);
			const size_t position = ref.size();
			ref.push_back(null_t());

			if (entries_rule.parse(first, last, context, rcontext, attr))
			{
				ref.at(position) = attr;
				return true;
			}
		}

		first = saved;
		return false;
	}
};

const auto map_rule_def = map_parser();
const auto entries_rule_def = *((value_rule - x3::lit('Z')) >> value_rule) >> x3::lit('Z');

BOOST_SPIRIT_DEFINE(map_rule, entries_rule);

}

using map::map_rule;

}
}
