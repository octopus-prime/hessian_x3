/*
 * string_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/binary.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <string>

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef std::string string_t;

namespace parser {
namespace detail {

//string ::= s b1 b0 <utf8-data> string
//       ::= S b1 b0 <utf8-data>
//       ::= [x00-x1f] <utf8-data>

// NOTE: The length means number of UTF16 characters but the content is given in UTF8 characters!

struct bstring : x3::parser<bstring>
{
    using attribute_type = hessian::string_t;

    template <typename It>
    using u8_u16_iterator = boost::u32_to_u16_iterator<boost::u8_to_u32_iterator<It>>;

    template <typename It>
    using u16_u8_iterator = boost::u32_to_u8_iterator<boost::u16_to_u32_iterator<It>>;

    template <typename It, typename Ctx, typename Attr>
	bool parse(It& f, It const& l, Ctx&, x3::unused_type, Attr& attr) const
    {
		auto saved = f;
		char type;
		size_t len;
		auto tied = std::tie(type, len);

		const u8_u16_iterator<It> e(l);
		while (x3::parse(f,l,x3::char_("sS") >> x3::big_word,tied))
		{
//			if (!x3::parse(f,l,x3::repeat(len)[x3::char_],attr))
//				break;
			u8_u16_iterator<It> b(f);
			std::u16string temp;
			while (temp.size() != len)
			{
				if (f == l)
					return false;
				if (b == e)
					return false;
				temp.push_back(*b++);
				f = b.base().base();
			}
			std::copy
			(
				u16_u8_iterator<std::u16string::const_iterator>(temp.cbegin()),
				u16_u8_iterator<std::u16string::const_iterator>(temp.cend()),
				std::back_inserter(attr)
			);
			if (type == 'S')
				return true;
		}

		f = saved;
		return false;
	}
};

std::string what(bstring const& p)
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

const auto string_rule = bstring();

}

using detail::string_rule;

}
}
