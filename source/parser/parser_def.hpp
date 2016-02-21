/*
 * parser_def.hpp
 *
 *  Created on: 20.02.2016
 *      Author: mgresens
 */

#pragma once

namespace hessian {
namespace parser {

struct definitions_tag;
typedef std::vector<std::string> class_t;
typedef std::vector<class_t> definitions_t;

namespace def {

const x3::rule<class def_rule, value_t> def_rule("def");
const x3::rule<class class_rule, class_t> class_rule("class");
const x3::rule<class length_rule, size_t> length_rule;

struct class_parser : x3::parser<class_parser>
{
    using attribute_type = definitions_t;

    template <typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator& first, const Iterator& last, const Context& context, RContext& rcontext, Attribute& attr) const
    {
		const auto saved = first;
		size_t length = 0;

		if (length_rule.parse(first, last, context, rcontext, length))
		{
			const auto rule = x3::repeat(length) [string_rule];
			if (rule.parse(first, last, context, rcontext, attr))
				return true;
		}

		first = saved;
		return false;
	}
};

const auto class_action = [](auto& ctx)
{
	definitions_t& definitions = x3::get<definitions_tag>(ctx);
	const class_t& clazz = x3::_attr(ctx);
	definitions.push_back(clazz);
};

const auto copy_action = [](auto& ctx)
{
	x3::_val(ctx) = x3::_attr(ctx);
};

const auto def_rule_def = class_rule [ class_action ] >> value_rule [ copy_action ];
const auto class_rule_def = class_parser();
const auto length_rule_def = x3::lit('C') >> x3::omit [string_rule] >> int_rule;

BOOST_SPIRIT_DEFINE(def_rule, class_rule, length_rule);

}

using def::def_rule;

}
}
