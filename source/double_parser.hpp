/*
 * double_parser.hpp
 *
 *  Created on: 03.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/binary.hpp>

namespace x3 = boost::spirit::x3;

namespace hessian {

typedef double double_t;

namespace parser {
namespace detail {

const auto double5_action = [](auto& ctx)
{
	x3::_val(ctx) = 0.001 * static_cast<std::int32_t>(x3::_attr(ctx));
};

const auto double6_action = [](auto& ctx)
{
	x3::_val(ctx) = reinterpret_cast<double&>(x3::_attr(ctx));
};

const x3::rule<class double_rule, double_t> double_rule("double");
const x3::rule<class double1_rule, double_t> double1_rule;
const x3::rule<class double2_rule, double_t> double2_rule;
const x3::rule<class double3_rule, std::int8_t> double3_rule;
const x3::rule<class double4_rule, std::int16_t> double4_rule;
const x3::rule<class double5_rule, double_t> double5_rule;
const x3::rule<class double6_rule, double_t> double6_rule;

const auto double_rule_def = double1_rule | double2_rule | double3_rule | double4_rule | double5_rule | double6_rule;
const auto double1_rule_def = x3::lit('\x5b') >> x3::attr(0.0);
const auto double2_rule_def = x3::lit('\x5c') >> x3::attr(1.0);
const auto double3_rule_def = x3::lit('\x5d') >> x3::byte_;
const auto double4_rule_def = x3::lit('\x5e') >> x3::big_word;
const auto double5_rule_def = x3::lit('\x5f') >> x3::big_dword [ double5_action ];
const auto double6_rule_def = x3::lit('D') >> x3::big_qword [ double6_action ]; // TODO: Replace by big_bin_double

BOOST_SPIRIT_DEFINE(double_rule, double1_rule, double2_rule, double3_rule, double4_rule, double5_rule, double6_rule);

}

using detail::double_rule;

}
}
