/*
 * list_parser.hpp
 *
 *  Created on: 29.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>
#include <vector>

namespace x3 = boost::spirit::x3;

namespace hessian {

template <typename T>
using list_t = std::vector<T>;

namespace parser {
namespace detail {

//list ::= V type? length? value* z
//     ::= v int int value*

const auto list_rule = [](const auto& rule)
{
	//TODO: How to provide rule name here?!
	//TODO: Finish grammar
	return x3::lit('V') >> *(rule - x3::lit('z')) >> x3::lit('z');
};

}

using detail::list_rule;

}
}
