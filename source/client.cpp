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
#include <array>
#include <boost/thread/shared_mutex.hpp>

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
	class post
	{
	public:
		post(const std::shared_ptr<CURLSH>& handle)
		:
			_error{{0}},
			_handle(curl_easy_init(), curl_easy_cleanup)
		{
			set_option(CURLOPT_SHARE, handle.get());
			set_option(CURLOPT_ERRORBUFFER, _error.data());
			set_option(CURLOPT_POST, 1L);
			set_option(CURLOPT_WRITEFUNCTION, write);
			set_option(CURLOPT_USERAGENT, "libhessian/1.0");
			set_option(CURLOPT_HTTPHEADER, HEADER.get());
			set_option(CURLOPT_VERBOSE, 0L);
		}

		std::string
		operator()(const string_t& url, const string_t& call) const
		{
			std::ostringstream output;

			set_option(CURLOPT_URL, url.c_str());
			set_option(CURLOPT_POSTFIELDS, call.data());
			set_option(CURLOPT_POSTFIELDSIZE, call.size());
			set_option(CURLOPT_WRITEDATA, &output);

			const auto result = perform();

			if (result != 200)
				throw std::runtime_error(std::to_string(result) + " " + __func__);

			return output.str();
		}

	protected:
		std::string
		get_error(const CURLcode code) const
		{
			return _error.front() != 0 ? _error.data() : curl_easy_strerror(code);
		}

		template <typename T>
		void
		set_option(const CURLoption key, const T value) const
		{
			const CURLcode code = curl_easy_setopt(_handle.get(), key, value);
			if (code != CURLE_OK)
				throw std::runtime_error(get_error(code) + " " + __func__);
		}

		long
		perform() const
		{
			CURLcode code = curl_easy_perform(_handle.get());

			if (code != CURLE_OK)
				throw std::runtime_error(get_error(code) + " " + __func__);

			long result;

			code = curl_easy_getinfo(_handle.get(), CURLINFO_RESPONSE_CODE, &result);
			if (code != CURLE_OK)
				throw std::runtime_error(get_error(code) + " " + __func__);

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
		std::array<char, CURL_ERROR_SIZE> _error;
		std::shared_ptr<CURL> _handle;

		static const std::shared_ptr<curl_slist> HEADER;
};

public:
	client_impl(const std::string& host)
	:
		_url(host),
		_mutex_cookie(),
		_mutex_dns(),
		_mutex_ssl(),
		_mutex_connect(),
		_handle(curl_share_init(), curl_share_cleanup)
	{
		set_option(CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
		set_option(CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
		set_option(CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
		set_option(CURLSHOPT_SHARE, CURL_LOCK_DATA_CONNECT);
		set_option(CURLSHOPT_LOCKFUNC, lock);
		set_option(CURLSHOPT_UNLOCKFUNC, unlock);
		set_option(CURLSHOPT_USERDATA, this);
	}

	virtual value_t call(const string_t& service, const string_t& method, const list_t& arguments) override
	{
		const string_t url = _url + service;
		const string_t call = generate(method, arguments);

		const post request(_handle);
		const std::string result = request(url, call);

		const content_t content = parse(result);
		return boost::apply_visitor(content_visitor(), content);
	}

protected:
	std::string
	get_error(const CURLSHcode code) const
	{
		return curl_share_strerror(code);
	}

	template <typename T>
	void
	set_option(const CURLSHoption key, const T value) const
	{
		const CURLSHcode code = curl_share_setopt(_handle.get(), key, value);
		if (code != CURLSHE_OK)
			throw std::runtime_error(get_error(code) + " " + __func__);
	}

	static void
	lock(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr)
	{
		client_impl* client = reinterpret_cast<client_impl*>(userptr);
		switch (data)
		{
		case CURL_LOCK_DATA_COOKIE:
			access == CURL_LOCK_ACCESS_SHARED
				? client->_mutex_cookie.lock_shared()
				: client->_mutex_cookie.lock();
			break;
		case CURL_LOCK_DATA_DNS:
			access == CURL_LOCK_ACCESS_SHARED
				? client->_mutex_dns.lock_shared()
				: client->_mutex_dns.lock();
			break;
		case CURL_LOCK_DATA_SSL_SESSION:
			access == CURL_LOCK_ACCESS_SHARED
				? client->_mutex_ssl.lock_shared()
				: client->_mutex_ssl.lock();
			break;
		case CURL_LOCK_DATA_CONNECT:
			access == CURL_LOCK_ACCESS_SHARED
				? client->_mutex_connect.lock_shared()
				: client->_mutex_connect.lock();
			break;
		default:
			break;
		}
	}

	static void
	unlock(CURL *handle, curl_lock_data data, void *userptr)
	{
		client_impl* client = reinterpret_cast<client_impl*>(userptr);
		switch (data)
		{
		case CURL_LOCK_DATA_COOKIE:
			client->_mutex_cookie.unlock();
			break;
		case CURL_LOCK_DATA_DNS:
			client->_mutex_dns.unlock();
			break;
		case CURL_LOCK_DATA_SSL_SESSION:
			client->_mutex_ssl.unlock();
			break;
		case CURL_LOCK_DATA_CONNECT:
			client->_mutex_connect.unlock();
			break;
		default:
			break;
		}
	}

private:
	std::string _url;
	boost::shared_mutex _mutex_cookie;
	boost::shared_mutex _mutex_dns;
	boost::shared_mutex _mutex_ssl;
	boost::shared_mutex _mutex_connect;
	std::shared_ptr<CURLSH> _handle;
};

const std::shared_ptr<curl_slist>
client_impl::post::HEADER(curl_slist_append(nullptr, "Content-Type: x-application/hessian"), curl_slist_free_all);

client_t
make_client(const std::string& host)
{
	return std::make_shared<client_impl>(host);
}

}
