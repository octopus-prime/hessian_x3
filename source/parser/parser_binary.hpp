/*
 * parser_binary.hpp
 *
 *  Created on: 20.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/fusion/adapted/std_tuple.hpp>

namespace hessian {
namespace parser {
namespace binary {

const x3::rule<class binary_rule, binary_t> binary_rule("binary");
const x3::rule<class length_rule, std::tuple<size_t,bool>> length_rule;
const x3::rule<class length1_rule, size_t> length1_rule;
const x3::rule<class length2_rule, size_t> length2_rule;
const x3::rule<class length3_rule, size_t> length3_rule;
const x3::rule<class length4_rule, size_t> length4_rule;

struct binary_parser : x3::parser<binary_parser>
{
    using attribute_type = binary_t;

    template <typename Iterator, typename Context, typename Attribute>
    bool parse(Iterator& first, const Iterator& last, const Context&, x3::unused_type, Attribute& attr) const
    {
		const auto saved = first;
		size_t length = 0;
		bool done = false;
		auto tied = std::tie(length, done);

		while (x3::parse(first, last, length_rule, tied))
		{
			const auto rule = x3::repeat(length) [x3::byte_];
			if (!x3::parse(first, last, rule, attr))
				break;

			if (done)
				return true;
		}

		first = saved;
		return false;
	}
};

const auto binary_rule_def = binary_parser();
const auto length_rule_def = ((length1_rule | length2_rule | length3_rule) >> x3::attr(true)) | (length4_rule >> x3::attr(false));
const auto length1_rule_def = byte_rule(0x20, 0x2f) [ calc_action<size_t,0>(0x20) ];
const auto length2_rule_def = (byte_rule(0x34, 0x37) >> x3::byte_) [ calc_action<size_t,8>(0x34) ];
const auto length3_rule_def = x3::lit('B') >> x3::big_word;
const auto length4_rule_def = x3::lit('A') >> x3::big_word;

BOOST_SPIRIT_DEFINE(binary_rule, length_rule, length1_rule, length2_rule, length3_rule, length4_rule);

}

using binary::binary_rule;

}
}
