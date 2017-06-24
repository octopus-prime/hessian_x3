/*
 * client.cpp
 *
 *  Created on: 23.02.2016
 *      Author: mike_gresens
 */

#include <hessian/client.hpp>
#include <hessian/parser.hpp>
#include <hessian/generator.hpp>
#include <beast/version.hpp>
#include <beast/core.hpp>
#include <beast/http.hpp>
#include <boost/asio.hpp>

using namespace std::literals;

namespace hessian {

class fault_exception_impl : public virtual fault_exception
{
public:
    fault_exception_impl(const fault_t& fault)
    :
        _fault(fault),
        _what(_fault.at("message"s).as<string_t>())
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

struct content_visitor
{
	const value_t& operator()(const reply_t& content) const
    {
        return content;
    }

	const value_t& operator()(const fault_t& content) const
    {
        throw fault_exception_impl(content);
    }
};

class client_impl : public virtual client_base
{
public:
    client_impl(const string_t& host, const string_t& port)
    :
        _service(),
        _socket(_service),
		_header(),
		_buffer()
    {
        boost::asio::ip::tcp::resolver resolver{_service};
        boost::asio::connect(_socket, resolver.resolve({host, port}));

        _header.method(beast::http::verb::post);
        _header.set(beast::http::field::host, host);
        _header.set(beast::http::field::user_agent, "libhessian/1.0 (" BEAST_VERSION_STRING ")");
        _header.set(beast::http::field::content_type, "x-application/hessian");
    }

    virtual value_t call(const string_t& service, const string_t& method, const list_t& arguments) override
    {
        beast::http::request<beast::http::string_body> request(_header);
        request.target(service);
        request.body = generate(method, arguments);
        request.prepare_payload();
        beast::http::write(_socket, request);

        beast::http::response<beast::http::string_body> response;
        beast::http::read(_socket, _buffer, response);

        const content_t content = parse(response.body);
        return std::visit(content_visitor(), content);
    }

private:
    boost::asio::io_service _service;
    boost::asio::ip::tcp::socket _socket;
    beast::http::header<true> _header;
    beast::flat_buffer _buffer;
};

client_t
make_client(const string_t& host, const string_t& port)
{
    return std::make_shared<client_impl>(host, port);
}

}
