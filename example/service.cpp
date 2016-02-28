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

	virtual bool replyTrue() override
	{
		return boost::get<hessian::bool_t>(call("replyTrue", {}));
	}

	virtual bool replyFalse() override
	{
		return boost::get<hessian::bool_t>(call("replyFalse", {}));
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

	virtual boost::posix_time::ptime replyDate_0() override
	{
		return boost::get<hessian::date_t>(call("replyDate_0", {}));
	}

	virtual boost::posix_time::ptime replyDate_1() override
	{
		return boost::get<hessian::date_t>(call("replyDate_1", {}));
	}

	virtual boost::posix_time::ptime replyDate_2() override
	{
		return boost::get<hessian::date_t>(call("replyDate_2", {}));
	}

	virtual std::string replyString_0() override
	{
		return boost::get<hessian::string_t>(call("replyString_0", {}));
	}

	virtual std::string replyString_1() override
	{
		return boost::get<hessian::string_t>(call("replyString_1", {}));
	}

	virtual std::string replyString_31() override
	{
		return boost::get<hessian::string_t>(call("replyString_31", {}));
	}

	virtual std::string replyString_1023() override
	{
		return boost::get<hessian::string_t>(call("replyString_1023", {}));
	}

	virtual std::basic_string<std::uint8_t> replyBinary_0() override
	{
		return boost::get<hessian::binary_t>(call("replyBinary_0", {}));
	}

	virtual std::basic_string<std::uint8_t> replyBinary_1() override
	{
		return boost::get<hessian::binary_t>(call("replyBinary_1", {}));
	}

	virtual bool argTrue(const bool arg) override
	{
		return boost::get<hessian::bool_t>(call("argTrue", {arg}));
	}

	virtual bool argFalse(const bool arg) override
	{
		return boost::get<hessian::bool_t>(call("argFalse", {arg}));
	}

	virtual bool argInt_0(const std::int32_t arg) override
	{
		return boost::get<hessian::bool_t>(call("argInt_0", {arg}));
	}

	virtual bool argInt_1(const std::int32_t arg) override
	{
		return boost::get<hessian::bool_t>(call("argInt_1", {arg}));
	}

	virtual bool argLong_0(const std::int64_t arg) override
	{
		return boost::get<hessian::bool_t>(call("argLong_0", {arg}));
	}

	virtual bool argLong_1(const std::int64_t arg) override
	{
		return boost::get<hessian::bool_t>(call("argLong_1", {arg}));
	}

	virtual bool argDouble_0(const double arg) override
	{
		return boost::get<hessian::bool_t>(call("argDouble_0_0", {arg}));
	}

	virtual bool argDouble_1(const double arg) override
	{
		return boost::get<hessian::bool_t>(call("argDouble_1_0", {arg}));
	}

	virtual bool argDate_0(const boost::posix_time::ptime& arg) override
	{
		return boost::get<hessian::bool_t>(call("argDate_0", {arg}));
	}

	virtual bool argDate_1(const boost::posix_time::ptime& arg) override
	{
		return boost::get<hessian::bool_t>(call("argDate_1", {arg}));
	}

	virtual bool argDate_2(const boost::posix_time::ptime& arg) override
	{
		return boost::get<hessian::bool_t>(call("argDate_2", {arg}));
	}

	virtual bool argString_0(const std::string& arg) override
	{
		return boost::get<hessian::bool_t>(call("argString_0", {arg}));
	}

	virtual bool argString_1(const std::string& arg) override
	{
		return boost::get<hessian::bool_t>(call("argString_1", {arg}));
	}

	virtual bool argString_31(const std::string& arg) override
	{
		return boost::get<hessian::bool_t>(call("argString_31", {arg}));
	}

	virtual bool argString_1023(const std::string& arg) override
	{
		return boost::get<hessian::bool_t>(call("argString_1023", {arg}));
	}

	virtual bool argBinary_0(const std::basic_string<std::uint8_t>& arg) override
	{
		return boost::get<hessian::bool_t>(call("argBinary_0", {arg}));
	}

	virtual bool argBinary_1(const std::basic_string<std::uint8_t>& arg) override
	{
		return boost::get<hessian::bool_t>(call("argBinary_1", {arg}));
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
