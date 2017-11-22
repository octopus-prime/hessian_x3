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

HESSIAN_ADAPT_STRUCT(caucho::Object, _value);
HESSIAN_ADAPT_STRUCT(caucho::Empty);
HESSIAN_ADAPT_STRUCT(caucho::Foo, id, name, date, keys);

namespace caucho {

class service_impl : public virtual service_base
{
public:
	service_impl(const hessian::client_t& client)
	:
		_client(client)
	{
	}

	virtual std::optional<std::string> replyString_null() override
	{
		return hessian::get<std::optional<std::string>>(call("replyString_null", {}));
	}

	virtual bool argString_null(const std::optional<std::string>& arg) //override
	{
		return hessian::get<bool>(call("argNull", {hessian::set(arg)}));
	}

	virtual std::vector<Object> replyObject_2() override
	{
		return hessian::get<std::vector<Object>>(call("replyObject_2", {}));
	}

	virtual std::vector<Empty> replyObject_16() override
	{
		return hessian::get<std::vector<Empty>>(call("replyObject_16", {}));
	}

	virtual bool argObject_2(const std::vector<Object>& arg) override
	{
		return hessian::get<bool>(call("argObject_2", {hessian::set(arg)}));
	}

	virtual bool argObject_16(const std::vector<Empty>& arg) override
	{
		return hessian::get<bool>(call("argObject_16", {hessian::set(arg)}));
	}

	virtual bool test_bool(const std::string& suffix) const override
	{
		const auto value = hessian::get<bool>(call("reply" + suffix, {}));
		return hessian::get<bool>(call("arg" + suffix, {hessian::set(value)}));
	}

	virtual bool test_int(const std::string& suffix) const override
	{
		const auto value = hessian::get<std::int32_t>(call("replyInt_" + suffix, {}));
		return hessian::get<bool>(call("argInt_" + suffix, {hessian::set(value)}));
	}

	virtual bool test_long(const std::string& suffix) const override
	{
		const auto value = hessian::get<std::int64_t>(call("replyLong_" + suffix, {}));
		return hessian::get<bool>(call("argLong_" + suffix, {hessian::set(value)}));
	}

	virtual bool test_double(const std::string& suffix) const override
	{
		const auto value = hessian::get<double>(call("replyDouble_" + suffix, {}));
		return hessian::get<bool>(call("argDouble_" + suffix, {hessian::set(value)}));
	}

	virtual bool test_date(const std::string& suffix) const override
	{
		const auto value = hessian::get<std::chrono::milliseconds>(call("replyDate_" + suffix, {}));
		return hessian::get<bool>(call("argDate_" + suffix, {hessian::set(value)}));
	}

	virtual bool test_string(const std::string& suffix) const override
	{
		const auto value = hessian::get<std::string>(call("replyString_" + suffix, {}));
		return hessian::get<bool>(call("argString_" + suffix, {hessian::set(value)}));
	}

	virtual bool test_binary(const std::string& suffix) const override
	{
		const auto value = hessian::get<std::basic_string<std::uint8_t>>(call("replyBinary_" + suffix, {}));
		return hessian::get<bool>(call("argBinary_" + suffix, {hessian::set(value)}));
	}

	virtual bool test_list(const std::string& suffix) const override
	{
		const auto value = hessian::get<std::vector<std::string>>(call("replyUntypedFixedList_" + suffix, {}));
		return hessian::get<bool>(call("argUntypedFixedList_" + suffix, {hessian::set(value)}));
	}

	virtual bool test_map_0() const override
	{
		const auto value = hessian::get<std::map<std::int32_t, std::int32_t>>(call("replyUntypedMap_0", {}));
		return hessian::get<bool>(call("argUntypedMap_0", {hessian::set(value)}));
	}

	virtual bool test_map_1() const override
	{
		const auto value = hessian::get<std::map<std::string, std::int32_t>>(call("replyUntypedMap_1", {}));
		return hessian::get<bool>(call("argUntypedMap_1", {hessian::set(value)}));
	}

	virtual bool test_map_2() const override
	{
		const auto value = hessian::get<std::map<std::int32_t, std::string>>(call("replyUntypedMap_2", {}));
		return hessian::get<bool>(call("argUntypedMap_2", {hessian::set(value)}));
	}

	virtual bool test_map_3() const override
	{
		const auto value = hessian::get<std::map<std::vector<std::string>, std::int32_t>>(call("replyUntypedMap_3", {}));
		return hessian::get<bool>(call("argUntypedMap_3", {hessian::set(value)}));
	}

	virtual void fault() override
	{
		call("doesNotExist", {});
	}

protected:
	hessian::value_t call(const hessian::string_t& method, const hessian::list_t& arguments) const
	{
		BOOST_LOG_TRIVIAL(info) << "Call " << method;
		const hessian::value_t value = _client->call("/test/test2", method, arguments);
		BOOST_LOG_TRIVIAL(debug) << "Got " << value;
		return value;
	}

private:
	hessian::client_t _client;
};

service_t
make_service(const std::string& host, const std::string& port)
{
	const hessian::client_t client = hessian::make_client(host, port);
	return std::make_shared<service_impl>(client);
}

}
