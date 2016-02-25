/*
 * parser_value_fwd.hpp
 *
 *  Created on: 25.02.2016
 *      Author: mgresens
 */

#pragma once

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace hessian {
namespace parser {

const x3::rule<class value_rule, value_t> value_rule("value");

}
}
