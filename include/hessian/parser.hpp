/*
 * parser.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <hessian/value.hpp>
#include <hessian/exception.hpp>

namespace hessian {

using reply_t = value_t;
using fault_t = map_t;
using content_t = std::variant<reply_t, fault_t>;

class parse_exception : public virtual exception {};

content_t parse(const std::string& data);

}
