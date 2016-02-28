/*
 * service.hpp
 *
 *  Created on: 28.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <cstdint>
#include <string>
#include <memory>

namespace caucho {

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
	virtual boost::posix_time::ptime replyDate_0() = 0;

	virtual bool argInt_0(const std::int32_t arg) = 0;
	virtual bool argLong_0(const std::int64_t arg) = 0;
	virtual bool argString_31(const std::string& arg) = 0;
	virtual bool argDate_0(const boost::posix_time::ptime& arg) = 0;

	virtual void fault() = 0;
};

typedef std::shared_ptr<service_base> service_t;

service_t make_service(const std::string& host);

}
