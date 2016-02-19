/*
 * parser.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <hessian/value.hpp>

namespace hessian {

value_t parse(std::istream& stream);
//value_t parse(const std::string& stream);

}
