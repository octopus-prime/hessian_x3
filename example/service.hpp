/*
 * service.hpp
 *
 *  Created on: 28.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <cstdint>
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <optional>
#include <memory>

namespace caucho {

struct Object
{
	std::int32_t _value;
};

struct Empty
{
};

struct Foo
{
	std::int32_t id;
	std::string name;
	std::optional<std::chrono::milliseconds> date;
	std::vector<std::int32_t> keys;
};

class service_base
{
protected:
	virtual ~service_base() noexcept = default;

public:
	virtual std::optional<std::string> replyString_null() = 0;

	virtual std::vector<Object> replyObject_2() = 0;
	virtual std::vector<Empty> replyObject_16() = 0;

	virtual bool argObject_2(const std::vector<Object>& arg) = 0;
	virtual bool argObject_16(const std::vector<Empty>& arg) = 0;

	virtual bool test_bool(const std::string& suffix) const = 0;
	virtual bool test_int(const std::string& suffix) const = 0;
	virtual bool test_long(const std::string& suffix) const = 0;
	virtual bool test_double(const std::string& suffix) const = 0;
	virtual bool test_date(const std::string& suffix) const = 0;
	virtual bool test_string(const std::string& suffix) const = 0;
	virtual bool test_binary(const std::string& suffix) const = 0;
	virtual bool test_list(const std::string& suffix) const = 0;
	virtual bool test_map_0() const = 0;
	virtual bool test_map_1() const = 0;
	virtual bool test_map_2() const = 0;
	virtual bool test_map_3() const = 0;

	virtual void fault() = 0;
};

typedef std::shared_ptr<service_base> service_t;

service_t make_service(const std::string& host, const std::string& port);

}
