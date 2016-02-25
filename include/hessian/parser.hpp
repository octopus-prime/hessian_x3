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

typedef value_t reply_t;
typedef map_t fault_t;
typedef boost::variant<reply_t, fault_t> content_t;

//content_t parse(const std::string& stream);
content_t parse(std::string&& stream);

}
