/*
 * client.hpp
 *
 *  Created on: 23.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <hessian/value.hpp>
#include <hessian/exception.hpp>
#include <memory>

namespace hessian {

class fault_exception :	public virtual exception
{
public:
	virtual const map_t& fault() const noexcept = 0;
};

class client_base
{
protected:
	virtual ~client_base() noexcept = default;

public:
	virtual value_t call(const string_t& service, const string_t& method, const list_t& arguments) = 0;
	virtual bool negotiate(const string_t& resource) = 0;
};

typedef std::shared_ptr<client_base> client_t;

client_t make_client(const string_t& url);

}
