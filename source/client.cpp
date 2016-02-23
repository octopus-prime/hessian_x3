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
//		request << header("Connection", "close");
		request << header("Content-Length", std::to_string(out.size()));
		request << body(out);

		http::client::response response = _client.post(request);
		std::stringstream stream(body(response));
		char c;
		stream >> c >> c >> c >> c;
		return hessian::parse(stream);
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
