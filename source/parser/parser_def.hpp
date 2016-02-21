/*
 * parser_def.hpp
 *
 *  Created on: 20.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {

struct def_tag;
typedef std::vector<std::vector<std::string>> def_t;

namespace def {

const x3::rule<class def_rule, value_t> def_rule("def");
const x3::rule<class length_rule, size_t> length_rule;

struct def_parser : x3::parser<def_parser>
{
    using attribute_type = def_t;

    template <typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator& first, const Iterator& last, const Context& context, RContext& rcontext, Attribute& attr) const
    {
		const auto saved = first;
		size_t length = 0;

		if (length_rule.parse(first, last, context, rcontext, length))
		{
			const auto rule = x3::repeat(length) [string_rule];
			std::vector<std::string> members;

			if (rule.parse(first, last, context, rcontext, members))
			{
				def_t& def = x3::get<def_tag>(context);
				def.push_back(members);

				if (value_rule.parse(first, last, context, rcontext, attr))
					return true;
			}
		}

		first = saved;
		return false;
	}
};

const auto def_rule_def = def_parser();
const auto length_rule_def = x3::lit('C') >> x3::omit [string_rule] >> int_rule;

BOOST_SPIRIT_DEFINE(def_rule, length_rule);

}

using def::def_rule;

}
}
