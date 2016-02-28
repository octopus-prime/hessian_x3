/*
 * example.cpp
 *
 *  Created on: 28.01.2016
 *      Author: mike_gresens
 */

#include "service.hpp"
#include <boost/date_time.hpp>

int main()
{
	try
	{
		const caucho::service_t service = caucho::make_service("http://hessian.caucho.com");

		std::cout << std::boolalpha;
		std::cout << service->replyInt_0() << std::endl;
		std::cout << service->replyInt_1() << std::endl;
		std::cout << service->replyLong_0() << std::endl;
		std::cout << service->replyLong_1() << std::endl;
		std::cout << service->replyDouble_0() << std::endl;
		std::cout << service->replyDouble_1() << std::endl;
		std::cout << service->replyString_31() << std::endl;
		std::cout << service->replyString_1023() << std::endl;
		std::cout << service->replyDate_0() << std::endl;

		std::cout << service->argInt_0(0) << std::endl;
		std::cout << service->argLong_0(0) << std::endl;
		std::cout << service->argString_31("0123456789012345678901234567890") << std::endl;
		std::cout << service->argDate_0(boost::posix_time::from_iso_string("19700101T000000")) << std::endl;

		service->fault();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
	}
	return 0;
}
