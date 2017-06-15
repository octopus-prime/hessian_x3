/*
 * service.hpp
 *
 *  Created on: 28.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/optional.hpp>
#include <boost/functional/hash.hpp>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>

namespace std {

template <>
struct hash<std::vector<std::string>>
{
	size_t operator()(const std::vector<std::string>& list) const
	{
		return boost::hash_value(list);
	}
};

}

namespace caucho {

struct Object
{
	std::int32_t _value;
};

struct Foo
{
	std::int32_t id;
	std::string name;
	boost::optional<boost::posix_time::ptime> date;
	std::vector<std::int32_t> keys;
};

class service_base
{
protected:
	virtual ~service_base() noexcept = default;

public:
	virtual bool replyTrue() = 0;
	virtual bool replyFalse() = 0;

	virtual std::int32_t replyInt_0() = 0;
	virtual std::int32_t replyInt_1() = 0;

	virtual std::int64_t replyLong_0() = 0;
	virtual std::int64_t replyLong_1() = 0;

	virtual double replyDouble_0() = 0;
	virtual double replyDouble_1() = 0;

	virtual boost::posix_time::ptime replyDate_0() = 0;
	virtual boost::posix_time::ptime replyDate_1() = 0;
	virtual boost::posix_time::ptime replyDate_2() = 0;

	virtual std::string replyString_0() = 0;
	virtual std::string replyString_1() = 0;
	virtual std::string replyString_31() = 0;
	virtual std::string replyString_1023() = 0;
	virtual boost::optional<std::string> replyString_null() = 0;

	virtual std::basic_string<std::uint8_t> replyBinary_0() = 0;
	virtual std::basic_string<std::uint8_t> replyBinary_1() = 0;

	virtual std::vector<std::string> replyList_7() = 0;

	virtual std::unordered_map<std::int32_t, std::string> replyMap_2() = 0;
	virtual std::unordered_map<std::vector<std::string>, std::int32_t> replyMap_3() = 0;

	virtual std::vector<Object> replyObject_2() = 0;

	virtual bool argTrue(const bool arg) = 0;
	virtual bool argFalse(const bool arg) = 0;

	virtual bool argInt_0(const std::int32_t arg) = 0;
	virtual bool argInt_1(const std::int32_t arg) = 0;

	virtual bool argLong_0(const std::int64_t arg) = 0;
	virtual bool argLong_1(const std::int64_t arg) = 0;

	virtual bool argDouble_0(const double arg) = 0;
	virtual bool argDouble_1(const double arg) = 0;

	virtual bool argDate_0(const boost::posix_time::ptime& arg) = 0;
	virtual bool argDate_1(const boost::posix_time::ptime& arg) = 0;
	virtual bool argDate_2(const boost::posix_time::ptime& arg) = 0;

	virtual bool argString_0(const std::string& arg) = 0;
	virtual bool argString_1(const std::string& arg) = 0;
	virtual bool argString_31(const std::string& arg) = 0;
	virtual bool argString_1023(const std::string& arg) = 0;
	virtual bool argString_null(const boost::optional<std::string>& arg) = 0;

	virtual bool argBinary_0(const std::basic_string<std::uint8_t>& arg) = 0;
	virtual bool argBinary_1(const std::basic_string<std::uint8_t>& arg) = 0;

	virtual bool argList_7(const std::vector<std::string>& arg) = 0;

	virtual bool argMap_2(const std::unordered_map<std::int32_t, std::string>& arg) = 0;
	virtual bool argMap_3(const std::unordered_map<std::vector<std::string>, std::int32_t>& arg) = 0;

	virtual bool argObject_2(const std::vector<Object>& arg) = 0;

	virtual void fault() = 0;
};

typedef std::shared_ptr<service_base> service_t;

service_t make_service(const std::string& host, const std::string& port);

}
