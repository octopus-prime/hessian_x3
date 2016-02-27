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

typedef value_t reply_t;
typedef map_t fault_t;
typedef boost::variant<reply_t, fault_t> content_t;

class parse_exception : public virtual exception {};

content_t parse(const std::string& data);

}
