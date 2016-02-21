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

class parse_exception : public virtual exception
{
public:
	virtual const char* what() const noexcept override;
};

value_t parse(std::istream& stream);
//value_t parse(const std::string& stream);

}
