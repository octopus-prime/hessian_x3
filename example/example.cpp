/*
 * example.cpp
 *
 *  Created on: 28.01.2016
 *      Author: mike_gresens
 */

#include "service.hpp"
#include <iostream>

int main()
{
	try
	{
		const caucho::service_t service = caucho::make_service("http://hessian.caucho.com");

		std::cout << std::boolalpha;

		std::cout << service->argTrue(service->replyTrue()) << std::endl;
		std::cout << service->argFalse(service->replyFalse()) << std::endl;

		std::cout << service->argInt_0(service->replyInt_0()) << std::endl;
		std::cout << service->argInt_1(service->replyInt_1()) << std::endl;

		std::cout << service->argLong_0(service->replyLong_0()) << std::endl;
		std::cout << service->argLong_1(service->replyLong_1()) << std::endl;

		std::cout << service->argDouble_0(service->replyDouble_0()) << std::endl;
		std::cout << service->argDouble_1(service->replyDouble_1()) << std::endl;

		std::cout << service->argDate_0(service->replyDate_0()) << std::endl;
		std::cout << service->argDate_1(service->replyDate_1()) << std::endl;
		std::cout << service->argDate_2(service->replyDate_2()) << std::endl;

		std::cout << service->argString_0(service->replyString_0()) << std::endl;
		std::cout << service->argString_1(service->replyString_1()) << std::endl;
		std::cout << service->argString_31(service->replyString_31()) << std::endl;
		std::cout << service->argString_1023(service->replyString_1023()) << std::endl;

		std::cout << service->argBinary_0(service->replyBinary_0()) << std::endl;
		std::cout << service->argBinary_1(service->replyBinary_1()) << std::endl;

		service->fault();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
	}
	return 0;
}
