/*
 * byte_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/binary.hpp>
#include <cstdint>

namespace x3 = boost::spirit::x3;

namespace hessian {
namespace parser {
namespace detail {

typedef std::int_fast8_t byte_t;

const auto byte_rule = [](const byte_t from, const byte_t to)
{
	const auto check = [from, to](auto& ctx)
	{
		const byte_t value = x3::_attr(ctx);
		x3::_val(ctx) = value;
		x3::_pass(ctx) = from <= value && value <= to;
	};

	return x3::byte_ [check];
};

}
}
}
