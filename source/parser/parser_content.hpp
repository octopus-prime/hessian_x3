/*
 * parser_content.hpp
 *
 *  Created on: 25.02.2016
 *      Author: mike_gresens
 */

#pragma once

using namespace std::literals;

namespace hessian {
namespace parser {
namespace content {

const x3::rule<class content_rule, content_t> content_rule;
const x3::rule<class reply_rule, reply_t> reply_rule;
const x3::rule<class fault_rule, fault_t> fault_rule;

const auto content_rule_def = x3::lit("H\x02\x00"s) >> (reply_rule | fault_rule);
const auto reply_rule_def = x3::lit('R') >> value_rule;
const auto fault_rule_def = x3::lit('F') >> map_rule;

BOOST_SPIRIT_DEFINE(content_rule, reply_rule, fault_rule);

}

using content::content_rule;

}
}
