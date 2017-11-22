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
		const auto service = caucho::make_service("hessian.caucho.com", "http");

		std::cout << std::boolalpha;

		for (auto suffix : {"True", "False"})
			std::cout << service->test_bool(suffix) << std::endl;

		for (auto suffix : {"0", "1", "47", "0x30", "0x7ff", "0x800", "0x3ffff", "0x40000", "0x7fffffff"})
			std::cout << service->test_int(suffix) << std::endl;
		for (auto suffix : {"m16", "m17", "m0x800", "m0x801", "m0x40000", "m0x40001", "m0x80000000"})
			std::cout << service->test_int(suffix) << std::endl;

		for (auto suffix : {"0", "1", "15", "0x10", "0x7ff", "0x800", "0x3ffff", "0x40000", "0x7fffffff", "0x80000000"})
			std::cout << service->test_long(suffix) << std::endl;
		for (auto suffix : {"m8", "m9", "m0x800", "m0x801", "m0x40000", "m0x40001", "m0x80000000", "m0x80000001"})
			std::cout << service->test_long(suffix) << std::endl;

		for (auto suffix : {"0_0", "0_001", "1_0", "2_0", "3_14159", "65_536", "127_0", "128_0", "32767_0"})
			std::cout << service->test_double(suffix) << std::endl;
		for (auto suffix : {"m0_001", "m128_0", "m129_0", "m32768_0"})
			std::cout << service->test_double(suffix) << std::endl;

		for (auto suffix : {"0", "1", "2"})
			std::cout << service->test_date(suffix) << std::endl;

		for (auto suffix : {"0", "1", "31", "32", "1023", "1024", "65536"})
			std::cout << service->test_string(suffix) << std::endl;

		for (auto suffix : {"0", "1", "15", "16", "1023", "1024", "65536"})
			std::cout << service->test_binary(suffix) << std::endl;

		for (auto suffix : {"0", "1", "7", "8"})
			std::cout << service->test_list(suffix) << std::endl;

		std::cout << service->test_map_0() << std::endl;
		std::cout << service->test_map_1() << std::endl;
		std::cout << service->test_map_2() << std::endl;
		std::cout << service->test_map_3() << std::endl;

		// 74 * 2 calls
//
//		std::cout << service->argMap_2(service->replyMap_2()) << std::endl;
//		std::cout << service->argMap_3(service->replyMap_3()) << std::endl;
//
//		std::cout << service->argObject_2(service->replyObject_2()) << std::endl;
//		std::cout << service->argObject_16(service->replyObject_16()) << std::endl;
//
//		service->fault();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
	}
	return 0;
}
