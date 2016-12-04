/*
 * client.cpp
 *
 *  Created on: 23.02.2016
 *      Author: mike_gresens
 */

#include <hessian/client.hpp>
#include <hessian/parser.hpp>
#include <hessian/generator.hpp>
#include <curl/curl.h>

using namespace std::literals;

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
		_client(curl_easy_init(), curl_easy_cleanup),
		_header(curl_slist_append(nullptr, "Content-Type: x-application/hessian"), curl_slist_free_all)
	{
//		set_option(CURLOPT_VERBOSE, 1L);
		set_option(CURLOPT_POST, 1L);
		set_option(CURLOPT_WRITEFUNCTION, write);
		set_option(CURLOPT_USERAGENT, "libhessian/1.0");
		set_option(CURLOPT_HTTPHEADER, _header.get());
	}

	virtual value_t call(const string_t& service, const string_t& method, const list_t& arguments) override
	{
		const string_t url = _url + service;
		const string_t call = generate(method, arguments);
		std::ostringstream output;

		set_option(CURLOPT_URL, url.c_str());
		set_option(CURLOPT_POSTFIELDS, call.data());
		set_option(CURLOPT_POSTFIELDSIZE, call.size());
		set_option(CURLOPT_WRITEDATA, &output);

		const auto result = perform();

		if (result != 200)
			throw std::runtime_error(std::to_string(result) + " " + __func__);

		const content_t content = parse(output.str());
		return boost::apply_visitor(content_visitor(), content);
	}

protected:
	template <typename T>
	void
	set_option(const CURLoption key, const T value) const
	{
		const CURLcode code = curl_easy_setopt(_client.get(), key, value);
		if (code != CURLE_OK)
			throw std::runtime_error(std::to_string(code) + " " + __func__);
	}

	long
	perform() const
	{
		CURLcode code = curl_easy_perform(_client.get());

		if (code != CURLE_OK)
			throw std::runtime_error(std::to_string(code) + " " + __func__);

		long result;

		code = curl_easy_getinfo(_client.get(), CURLINFO_RESPONSE_CODE, &result);
		if (code != CURLE_OK)
			throw std::runtime_error(std::to_string(code) + " " + __func__);

		return result;
	}

	static size_t
	write(char *buffer, size_t size, size_t nitems, void *outstream)
	{
		const size_t length = size * nitems;
		reinterpret_cast<std::ostream*>(outstream)->write(buffer, length);
		return length;
	}

private:
	std::string _url;
	std::shared_ptr<CURL> _client;
	std::shared_ptr<curl_slist> _header;
};

client_t
make_client(const std::string& host)
{
	return std::make_shared<client_impl>(host);
}

}

