/*
 * Test.cpp
 *
 *  Created on: 28.01.2016
 *      Author: mike_gresens
 */

#include <boost/spirit/home/x3.hpp>
#include "int_parser.hpp"
#include "long_parser.hpp"
#include "date_parser.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

namespace x3 = boost::spirit::x3;

void test_int()
{
	const std::string text("I\x00\x00\x01\x2c", 5);
	hessian::int_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::int_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}

void test_date()
{
	const std::string text("d\x00\x00\x00\xd0\x4b\x92\x84\xb8", 9);
	hessian::date_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::date_rule, attr) << std::endl;
	const std::time_t time = hessian::date_t::clock::to_time_t(attr);
	std::cout << std::put_time(std::gmtime(&time), "%F %T") << std::endl;
}

int main()
{
	try
	{
		test_int();
		test_date();
	}
	catch (const x3::expectation_failure<std::string::const_iterator>& exception)
	{
		std::cout << exception.what() << " " << exception.which() << " " << *exception.where() << std::endl;
	}
    return 0;
}
