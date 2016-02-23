/*
 * Test.cpp
 *
 *  Created on: 28.01.2016
 *      Author: mike_gresens
 */

#include <hessian/client.hpp>

using namespace std::literals;

class service_base
{
protected:
	virtual ~service_base() noexcept = default;

public:
	virtual std::int32_t replyInt_0() = 0;
	virtual std::int32_t replyInt_1() = 0;
	virtual std::int64_t replyLong_0() = 0;
	virtual std::int64_t replyLong_1() = 0;
	virtual double replyDouble_0() = 0;
	virtual double replyDouble_1() = 0;
	virtual std::string replyString_31() = 0;
	virtual std::string replyString_1023() = 0;
};

typedef std::shared_ptr<service_base> service_t;

class service_impl : public virtual service_base
{
public:
	service_impl(const std::string& host)
	:
		_client(hessian::connect(host))
	{
	}

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


protected:
	hessian::value_t call(const hessian::string_t& method, const hessian::value_t& arguments)
	{
		return _client->call("/test/test2", method, arguments);
	}

private:
	hessian::client_t _client;
};

int main()
{
	try
	{
		const hessian::client_t client = hessian::connect("http://hessian.caucho.com");
		const service_t service1 = std::make_shared<service_impl>(client);
		const service_t service2 = std::make_shared<service_impl>(client);

		std::cout << service1->replyInt_0() << std::endl;
		std::cout << service2->replyInt_1() << std::endl;
		std::cout << service1->replyLong_0() << std::endl;
		std::cout << service2->replyLong_1() << std::endl;
		std::cout << service1->replyDouble_0() << std::endl;
		std::cout << service2->replyDouble_1() << std::endl;
		std::cout << service1->replyString_31() << std::endl;
		std::cout << service2->replyString_1023() << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
    return 0;
}
