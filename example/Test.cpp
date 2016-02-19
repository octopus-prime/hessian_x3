/*
 * Test.cpp
 *
 *  Created on: 28.01.2016
 *      Author: mike_gresens
 */

#include <boost/spirit/home/x3.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "null_parser.hpp"
#include "bool_parser.hpp"
#include "int_parser.hpp"
#include "long_parser.hpp"
#include "date_parser.hpp"
#include "string_parser.hpp"
//#include "list_parser.hpp"
#include "map_parser.hpp"
#include "value_parser.hpp"
#include <iostream>
#include <iomanip>

namespace x3 = boost::spirit::x3;
using namespace std::literals;

void test_value()
{
	const std::string text("WL\x00\x00\x00\x00\x00\x00\x01\x2cNTFZ"s);
	hessian::value_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::value_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}
/*
void test_null()
{
	const std::string text("N"s);
	hessian::null_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::null_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}

void test_bool()
{
	const std::string text("T"s);
	hessian::bool_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::bool_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}

void test_int()
{
	const std::string text("I\x00\x00\x01\x2c"s);
	hessian::int_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::int_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}

void test_long()
{
	const std::string text("L\x00\x00\x00\x00\x00\x00\x01\x2c"s);
	hessian::long_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::long_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}

void test_date()
{
	const std::string text("d\x00\x00\x00\xd0\x4b\x92\x84\xb8"s);
	hessian::date_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::date_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}

void test_string()
{
	const std::string text("s\x00\x07hello, \x05world"s);
	hessian::string_t attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::string_rule, attr) << std::endl;
	std::cout << attr << std::endl;
}

void test_list()
{
	const std::string text("VTFFTz"s);
	hessian::list_t<hessian::bool_t> attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::list_rule(hessian::parser::bool_rule), attr) << std::endl;
	for (const auto element : attr)
		std::cout << element << ',';
	std::cout << std::endl;
}

void test_map()
{
	const std::string text("MTFFTz"s);
	hessian::map_t<hessian::bool_t, hessian::bool_t> attr;
	std::cout << x3::parse(text.begin(), text.end(), x3::eps > hessian::parser::map_rule(hessian::parser::bool_rule, hessian::parser::bool_rule), attr) << std::endl;
	for (const auto& element : attr)
		std::cout << element.first << "=" << element.second << ',';
	std::cout << std::endl;
}
*/
int main()
{
	try
	{
		std::cout << std::boolalpha;

		test_value();
//		test_null();
//		test_bool();
//		test_int();
//		test_long();
//		test_date();
//		test_string();
//		test_list();
//		test_map();
	}
	catch (const x3::expectation_failure<std::string::const_iterator>& exception)
	{
		std::cout << exception.what() << " " << exception.which() << " " << *exception.where() << std::endl;
	}
    return 0;
}