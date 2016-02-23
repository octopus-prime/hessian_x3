/*
 * Test.cpp
 *
 *  Created on: 28.01.2016
 *      Author: mike_gresens
 */

#include <hessian/parser.hpp>
#include <boost/network.hpp>

#include <iostream>
#include <iomanip>
#include <memory>

using namespace std::literals;
namespace net = boost::network;

typedef net::http::client client_t;

class service_base_t
{
protected:
	virtual ~service_base_t() noexcept = default;

public:
	virtual int replyInt_0() = 0;
	virtual int replyInt_1() = 0;
	virtual long replyLong_0() = 0;
	virtual long replyLong_1() = 0;
};

typedef std::shared_ptr<service_base_t> service_t;

class service_impl_t : public virtual service_base_t
{
public:
	service_impl_t(const std::string& host)
	:
		_url(host),
		_client(client_t::options().cache_resolved(true))
	{
		_url << net::uri::path("/test/test2");
	}

	virtual int replyInt_0() override
	{
		const std::string content("H\x02\x00""C\x0a""replyInt_0\x90"s);
		return boost::get<hessian::int_t>(call(content));
	}

	virtual int replyInt_1() override
	{
		const std::string content("H\x02\x00""C\x0a""replyInt_1\x90"s);
		return boost::get<hessian::int_t>(call(content));
	}

	virtual long replyLong_0() override
	{
		const std::string content("H\x02\x00""C\x0b""replyLong_0\x90"s);
		return boost::get<hessian::long_t>(call(content));
	}

	virtual long replyLong_1() override
	{
		const std::string content("H\x02\x00""C\x0b""replyLong_1\x90"s);
		return boost::get<hessian::long_t>(call(content));
	}

protected:
	hessian::value_t call(const std::string& content)
	{
		client_t::request request(_url);
		request << net::header("Content-Length", std::to_string(content.size()));
		request << net::body(content);

		client_t::response response = _client.post(request);
		std::stringstream stream(body(response));
		char c;
		stream >> c >> c >> c >> c;
		return hessian::parse(stream);
	}

private:
	net::uri::uri _url;
	client_t _client;
};

void test2()
{
	const service_t service = std::make_shared<service_impl_t>("http://hessian.caucho.com");
	std::cout << service->replyInt_0() << std::endl;
	std::cout << service->replyInt_1() << std::endl;
	std::cout << service->replyLong_0() << std::endl;
	std::cout << service->replyLong_1() << std::endl;
}
/*
void foo(client_t& client)
{
	const net::uri::uri url("http://hessian.caucho.com");
	const std::string content("H\x02\x00""C\x0a""replyInt_0\x90"s);

//	client_t::request request("http://hessian.caucho.com/test/test2");
	client_t::request request(net::uri::uri(url) << net::uri::path("test/test2"));
	request << net::header("Content-Length", std::to_string(content.size()));
	request << net::body(content);

	client_t::response response = client.post(request);
	std::stringstream stream(body(response));
	char c;
	stream >> c >> c >> c >> c;
	std::cout << hessian::parse(stream) << std::endl;
}

void test()
{
	client_t::options().cache_resolved(true);

	client_t client(options);

	foo(client);
	foo(client);
	foo(client);
	foo(client);
	foo(client);
}
*/
int main()
{
	try
	{
		std::cout << std::boolalpha;

		test2();
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
    return 0;
}
