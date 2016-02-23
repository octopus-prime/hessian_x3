/*
 * client.hpp
 *
 *  Created on: 23.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <hessian/value.hpp>
#include <memory>

namespace hessian {

class client_base
{
protected:
	virtual ~client_base() noexcept = default;

public:
	virtual value_t call(const string_t& service, const string_t& method, const value_t& arguments) = 0;
};

typedef std::shared_ptr<client_base> client_t;

client_t connect(const string_t& host);

}
