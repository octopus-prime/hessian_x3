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

template <typename T, size_t N>
class calc_action
{
public:
	calc_action(const T offset) : _offset(offset) {}

	template <typename C>
	void operator()(C& ctx) const
	{
		using boost::fusion::at_c;
		const T b1 = at_c<0>(x3::_attr(ctx));
		const T b0 = at_c<1>(x3::_attr(ctx));
		x3::_val(ctx) = ((b1 - _offset) << N) + b0;
	};

private:
	T _offset;
};

template <typename T>
struct calc_action<T, 0>
{
public:
	calc_action(const T offset) : _offset(offset) {}

	template <typename C>
	void operator()(C& ctx) const
	{
		const T b0 = x3::_attr(ctx);
		x3::_val(ctx) = b0 - _offset;
	}

private:
	T _offset;
};

}
}
}
