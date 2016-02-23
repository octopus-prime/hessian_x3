/*
 * Test.cpp
 *
 *  Created on: 28.01.2016
 *      Author: mike_gresens
 */

#include <hessian/client.hpp>

using namespace std::literals;

class service_base_t
{
protected:
	virtual ~service_base_t() noexcept = default;

public:
	virtual std::int32_t replyInt_0() = 0;
	virtual std::int32_t replyInt_1() = 0;
	virtual std::int64_t replyLong_0() = 0;
	virtual std::int64_t replyLong_1() = 0;
};

typedef std::shared_ptr<service_base_t> service_t;

class service_impl_t : public virtual service_base_t
{
public:
	service_impl_t(const std::string& host)
	:
		_client(hessian::connect(host))
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
		const service_t service = std::make_shared<service_impl_t>("http://hessian.caucho.com");

		std::cout << service->replyInt_0() << std::endl;
		std::cout << service->replyInt_1() << std::endl;
		std::cout << service->replyLong_0() << std::endl;
		std::cout << service->replyLong_1() << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
    return 0;
}
