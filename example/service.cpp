/*
 * service.cpp
 *
 *  Created on: 28.02.2016
 *      Author: mike_gresens
 */

#include "service.hpp"
#include <hessian/client.hpp>
#include <boost/log/trivial.hpp>

namespace caucho {

class service_impl : public virtual service_base
{
public:
	service_impl(const hessian::client_t& client)
	:
		_client(client)
	{
	}

	virtual std::int32_t replyInt_0() override
	{
		return boost::get<hessian::int_t>(call("replyInt_0", {}));
	}

	virtual std::int32_t replyInt_1() override
	{
		return boost::get<hessian::int_t>(call("replyInt_1", {}));
	}

	virtual std::int64_t replyLong_0() override
	{
		return boost::get<hessian::long_t>(call("replyLong_0", {}));
	}

	virtual std::int64_t replyLong_1() override
	{
		return boost::get<hessian::long_t>(call("replyLong_1", {}));
	}

	virtual double replyDouble_0() override
	{
		return boost::get<hessian::double_t>(call("replyDouble_0_0", {}));
	}

	virtual double replyDouble_1() override
	{
		return boost::get<hessian::double_t>(call("replyDouble_1_0", {}));
	}

	virtual std::string replyString_31() override
	{
		return boost::get<hessian::string_t>(call("replyString_31", {}));
	}

	virtual std::string replyString_1023() override
	{
		return boost::get<hessian::string_t>(call("replyString_1023", {}));
	}

	virtual boost::posix_time::ptime replyDate_0() override
	{
		return boost::get<hessian::date_t>(call("replyDate_0", {}));
	}

	virtual bool argInt_0(const std::int32_t arg) override
	{
		return boost::get<hessian::bool_t>(call("argInt_0", {arg}));
	}

	virtual bool argLong_0(const std::int64_t arg) override
	{
		return boost::get<hessian::bool_t>(call("argLong_0", {arg}));
	}

	virtual bool argString_31(const std::string& arg) override
	{
		return boost::get<hessian::bool_t>(call("argString_31", {arg}));
	}

	virtual bool argDate_0(const boost::posix_time::ptime& arg) override
	{
		return boost::get<hessian::bool_t>(call("argDate_0", {arg}));
	}

	virtual void fault() override
	{
		call("doesNotExist", {});
	}

protected:
	hessian::value_t call(const hessian::string_t& method, const hessian::list_t& arguments)
	{
		BOOST_LOG_TRIVIAL(info) << "Call " << method;
		const hessian::value_t value = _client->call("/test/test2", method, arguments);
		BOOST_LOG_TRIVIAL(info) << "Got " << value;
		return std::move(value);
	}

private:
	hessian::client_t _client;
};

service_t
make_service(const std::string& host)
{
	const hessian::client_t client = hessian::make_client(host);
	return std::make_shared<service_impl>(client);
}

}
