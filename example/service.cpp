/*
 * service.cpp
 *
 *  Created on: 28.02.2016
 *      Author: mike_gresens
 */

#include "service.hpp"
#include <hessian/client.hpp>
#include <hessian/helper.hpp>
#include <boost/log/trivial.hpp>

DEFINE_GET(caucho::Foo, (id)(name)(date)(keys));
DEFINE_SET(caucho::Foo, (id)(name)(date)(keys));

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
		return hessian::get<bool>(call("replyTrue", {}));
	}

	virtual bool replyFalse() override
	{
		return hessian::get<bool>(call("replyFalse", {}));
	}

	virtual std::int32_t replyInt_0() override
	{
		return hessian::get<std::int32_t>(call("replyInt_0", {}));
	}

	virtual std::int32_t replyInt_1() override
	{
		return hessian::get<std::int32_t>(call("replyInt_1", {}));
	}

	virtual std::int64_t replyLong_0() override
	{
		return hessian::get<std::int64_t>(call("replyLong_0", {}));
	}

	virtual std::int64_t replyLong_1() override
	{
		return hessian::get<std::int64_t>(call("replyLong_1", {}));
	}

	virtual double replyDouble_0() override
	{
		return hessian::get<double>(call("replyDouble_0_0", {}));
	}

	virtual double replyDouble_1() override
	{
		return hessian::get<double>(call("replyDouble_1_0", {}));
	}

	virtual boost::posix_time::ptime replyDate_0() override
	{
		return hessian::get<boost::posix_time::ptime>(call("replyDate_0", {}));
	}

	virtual boost::posix_time::ptime replyDate_1() override
	{
		return hessian::get<boost::posix_time::ptime>(call("replyDate_1", {}));
	}

	virtual boost::posix_time::ptime replyDate_2() override
	{
		return hessian::get<boost::posix_time::ptime>(call("replyDate_2", {}));
	}

	virtual std::string replyString_0() override
	{
		return hessian::get<std::string>(call("replyString_0", {}));
	}

	virtual std::string replyString_1() override
	{
		return hessian::get<std::string>(call("replyString_1", {}));
	}

	virtual std::string replyString_31() override
	{
		return hessian::get<std::string>(call("replyString_31", {}));
	}

	virtual std::string replyString_1023() override
	{
		return hessian::get<std::string>(call("replyString_1023", {}));
	}

	virtual boost::optional<std::string> replyString_null() override
	{
		return hessian::get<boost::optional<std::string>>(call("replyString_null", {}));
	}

	virtual std::basic_string<std::uint8_t> replyBinary_0() override
	{
		return hessian::get<std::basic_string<std::uint8_t>>(call("replyBinary_0", {}));
	}

	virtual std::basic_string<std::uint8_t> replyBinary_1() override
	{
		return hessian::get<std::basic_string<std::uint8_t>>(call("replyBinary_1", {}));
	}

	virtual std::vector<std::string> replyList_7() override
	{
		return hessian::get<std::vector<std::string>>(call("replyUntypedFixedList_7", {}));
	}

	virtual std::unordered_map<std::int32_t, std::string> replyMap_2() override
	{
		return hessian::get<std::unordered_map<std::int32_t, std::string>>(call("replyUntypedMap_2", {}));
	}

	virtual std::unordered_map<std::vector<std::string>, std::int32_t> replyMap_3() override
	{
		return hessian::get<std::unordered_map<std::vector<std::string>, std::int32_t>>(call("replyUntypedMap_3", {}));
//		return hessian::get<std::result_of_t<decltype(&service_base::replyMap_3)(decltype(this))>>(call("replyUntypedMap_3", {}));
	}

	virtual bool argTrue(const bool arg) override
	{
		return hessian::get<bool>(call("argTrue", {hessian::set(arg)}));
	}

	virtual bool argFalse(const bool arg) override
	{
		return hessian::get<bool>(call("argFalse", {hessian::set(arg)}));
	}

	virtual bool argInt_0(const std::int32_t arg) override
	{
		return hessian::get<bool>(call("argInt_0", {hessian::set(arg)}));
	}

	virtual bool argInt_1(const std::int32_t arg) override
	{
		return hessian::get<bool>(call("argInt_1", {hessian::set(arg)}));
	}

	virtual bool argLong_0(const std::int64_t arg) override
	{
		return hessian::get<bool>(call("argLong_0", {hessian::set(arg)}));
	}

	virtual bool argLong_1(const std::int64_t arg) override
	{
		return hessian::get<bool>(call("argLong_1", {hessian::set(arg)}));
	}

	virtual bool argDouble_0(const double arg) override
	{
		return hessian::get<bool>(call("argDouble_0_0", {hessian::set(arg)}));
	}

	virtual bool argDouble_1(const double arg) override
	{
		return hessian::get<bool>(call("argDouble_1_0", {hessian::set(arg)}));
	}

	virtual bool argDate_0(const boost::posix_time::ptime& arg) override
	{
		return hessian::get<bool>(call("argDate_0", {hessian::set(arg)}));
	}

	virtual bool argDate_1(const boost::posix_time::ptime& arg) override
	{
		return hessian::get<bool>(call("argDate_1", {hessian::set(arg)}));
	}

	virtual bool argDate_2(const boost::posix_time::ptime& arg) override
	{
		return hessian::get<bool>(call("argDate_2", {hessian::set(arg)}));
	}

	virtual bool argString_0(const std::string& arg) override
	{
		return hessian::get<bool>(call("argString_0", {hessian::set(arg)}));
	}

	virtual bool argString_1(const std::string& arg) override
	{
		return hessian::get<bool>(call("argString_1", {hessian::set(arg)}));
	}

	virtual bool argString_31(const std::string& arg) override
	{
		return hessian::get<bool>(call("argString_31", {hessian::set(arg)}));
	}

	virtual bool argString_1023(const std::string& arg) override
	{
		return hessian::get<bool>(call("argString_1023", {hessian::set(arg)}));
	}

	virtual bool argString_null(const boost::optional<std::string>& arg) override
	{
		return hessian::get<bool>(call("argNull", {hessian::set(arg)}));
	}

	virtual bool argBinary_0(const std::basic_string<std::uint8_t>& arg) override
	{
		return hessian::get<bool>(call("argBinary_0", {hessian::set(arg)}));
	}

	virtual bool argBinary_1(const std::basic_string<std::uint8_t>& arg) override
	{
		return hessian::get<bool>(call("argBinary_1", {hessian::set(arg)}));
	}

	virtual bool argList_7(const std::vector<std::string>& arg) override
	{
		return hessian::get<bool>(call("argUntypedFixedList_7", {hessian::set(arg)}));
	}

	virtual bool argMap_2(const std::unordered_map<std::int32_t, std::string>& arg) override
	{
		return hessian::get<bool>(call("argUntypedMap_2", {hessian::set(arg)}));
	}

	virtual bool argMap_3(const std::unordered_map<std::vector<std::string>, std::int32_t>& arg) override
	{
		return hessian::get<bool>(call("argUntypedMap_3", {hessian::set(arg)}));
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
