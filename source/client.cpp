/*
 * client.cpp
 *
 *  Created on: 23.02.2016
 *      Author: mike_gresens
 */

#include <hessian/client.hpp>
#include <hessian/parser.hpp>
#include <boost/network.hpp>

using namespace std::literals;
using namespace boost::network;

namespace hessian {

class fault_exception_impl : public virtual fault_exception
{
public:
	fault_exception_impl(const fault_t& fault)
	:
		_fault(fault),
		_what(boost::get<string_t>(_fault.at("message"s)))
	{
	}

	virtual const char* what() const noexcept override
	{
		return _what.c_str();
	}

	virtual const map_t& fault() const noexcept override
	{
		return _fault;
	}

private:
	fault_t _fault;
	string_t _what;
};

struct content_visitor : boost::static_visitor<const value_t&>
{
	result_type operator()(const reply_t& content) const
	{
		return content;
	}

	result_type operator()(const fault_t& content) const
	{
		throw fault_exception_impl(content);
	}
};

class client_impl : public virtual client_base
{
public:
	client_impl(const std::string& host)
	:
		_url(host),
		_client(http::client::options().cache_resolved(true))
	{
	}

	virtual value_t call(const string_t& service, const string_t& method, const value_t& arguments) override
	{
		uri::uri url(_url);
		url << uri::path(service);

		std::string out = "H\x02\x00""C"s;
		out.push_back((std::uint8_t) method.size());
		out.append(method);
		out.push_back('\x90');

		http::client::request request(url);
		request << header("Connection", "close");
		request << header("Content-Length", std::to_string(out.size()));
		request << body(out);

		const http::client::response response = _client.post(request);
		const content_t content = hessian::parse(body(response));
		return boost::apply_visitor(content_visitor(), content);
	}

private:
	uri::uri _url;
	http::client _client;
};

client_t connect(const std::string& host)
{
	return std::make_shared<client_impl>(host);
}

}
