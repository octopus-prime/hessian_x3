/*
 * parser_string.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/fusion/adapted/std_tuple.hpp>

namespace hessian {
namespace parser {

//string ::= s b1 b0 <utf8-data> string
//       ::= S b1 b0 <utf8-data>
//       ::= [x00-x1f] <utf8-data>

// NOTE: The length means number of UTF16 characters but the content is given in UTF8 characters!

struct string_parser : x3::parser<string_parser>
{
    using attribute_type = hessian::string_t;

    template <typename It>
    using u8_u16_iterator = boost::u32_to_u16_iterator<boost::u8_to_u32_iterator<It>>;

    template <typename It, typename Ctx, typename Attr>
	bool parse(It& f, It const& l, Ctx&, x3::unused_type, Attr& attr) const
    {
		const auto saved = f;
		char type = 'S';
		size_t len;
		auto tied = std::tie(type, len);

//		const u8_u16_iterator<It> e(l);
		while (x3::parse(f,l,x3::char_("sS") >> x3::big_word,tied) || x3::parse(f,l,byte_rule(0x00, 0x1f), len))
		{
			u8_u16_iterator<It> i(f);
			// std::advance(i, len); // broken
			std::__advance(i, len, std::input_iterator_tag());

			const auto s = f;
			f = i.base().base();

			attr.insert(attr.cend(), s, f);

			if (type == 'S')
				return true;

			type = 'S';
		}

		f = saved;
		return false;
	}
};

std::string what(string_parser const& p)
{
    return "string";
}

/*
struct length_tag;
const auto length_action = [](auto& ctx)
{
	*x3::get<length_tag>(ctx) = x3::_attr(ctx);
};
const auto more_action = [](auto &ctx)
{
	x3::_pass(ctx) = *x3::get<length_tag>(ctx) >  x3::_val(ctx).size();
};
const auto done_action = [](auto &ctx)
{
	x3::_pass(ctx) = *x3::get<length_tag>(ctx) == x3::_val(ctx).size();
};
const auto push_action = [](auto &ctx)
{
	x3::_val(ctx).push_back(x3::_attr(ctx));
};

const x3::rule<class string_rule, string_t> string_rule("string");
const x3::rule<class string1_rule, string_t> string1_rule;
const x3::rule<class string2_rule, string_t> string2_rule;

const auto length_rule = x3::omit[x3::big_word [length_action] ];
const auto content_rule = x3::lexeme[ *(x3::eps [more_action] >> x3::char_ [push_action]) >> x3::eps [done_action] ];

const auto string_rule_def = x3::with<length_tag>(std::make_shared<std::size_t>())[string1_rule | string2_rule];
const auto string1_rule_def = x3::lit('S') >> length_rule >> content_rule;
const auto string2_rule_def = x3::lit('s') >> length_rule >> content_rule >> string_rule;

BOOST_SPIRIT_DEFINE(string_rule, string1_rule, string2_rule);
*/

//const x3::rule<class string_rule, string_t> string_rule("string");
//const auto string_rule_def = bstring();
//BOOST_SPIRIT_DEFINE(string_rule);

const auto string_rule = string_parser();

}
}
