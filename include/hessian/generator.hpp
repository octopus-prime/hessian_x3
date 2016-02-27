/*
 * generator.hpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <hessian/value.hpp>
#include <hessian/exception.hpp>

namespace hessian {

class generate_exception : public virtual exception {};

string_t generate(const string_t& method, const list_t& arguments);

}
