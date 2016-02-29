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
namespace string {

const x3::rule<class string_rule, string_t> string_rule("string");
const x3::rule<class length_rule, std::tuple<size_t,bool>> length_rule;
const x3::rule<class length1_rule, size_t> length1_rule;
const x3::rule<class length2_rule, size_t> length2_rule;
const x3::rule<class length3_rule, size_t> length3_rule;
const x3::rule<class length4_rule, size_t> length4_rule;

struct string_parser : x3::parser<string_parser>
{
    using attribute_type = string_t;

    template <typename Iterator>
    using u8_u16_iterator = boost::u32_to_u16_iterator<boost::u8_to_u32_iterator<Iterator>>;

    template <typename Iterator, typename Context, typename Attribute>
    bool parse(Iterator& first, const Iterator& last, const Context&, x3::unused_type, Attribute& attr) const
    {
		const auto saved = first;
		size_t length = 0;
		bool done = false;
		auto tied = std::tie(length, done);

		while (x3::parse(first, last, length_rule, tied))
		{
			// NOTE: The length means number of UTF16 characters but the content is given in UTF8 characters!
			u8_u16_iterator<Iterator> iterator(first);
			std::advance(iterator, length);

			const auto saved = first;
			first = iterator.base().base();

			if (first > last)
				break;

			x3::traits::append(attr, saved, first);

			if (done)
				return true;
		}

		first = saved;
		return false;
	}
};

const auto string_rule_def = string_parser();
const auto length_rule_def = ((length1_rule | length2_rule | length3_rule) >> x3::attr(true)) | (length4_rule >> x3::attr(false));
const auto length1_rule_def = byte_rule(0x00, 0x1f);
const auto length2_rule_def = (byte_rule(0x30, 0x33) >> x3::byte_) [ calc_action<size_t,8>(0x30) ];
const auto length3_rule_def = x3::lit('S') >> x3::big_word;
const auto length4_rule_def = x3::lit('R') >> x3::big_word;

BOOST_SPIRIT_DEFINE(string_rule, length_rule, length1_rule, length2_rule, length3_rule, length4_rule);

}

using string::string_rule;

}
}
