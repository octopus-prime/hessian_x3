/*
 * generator.cpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#include <hessian/generator.hpp>

using namespace std::literals;

namespace hessian {

class generate_exception_impl : public virtual generate_exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Generating failed.";
	}
};

string_t
generate(const string_t& method, const list_t& arguments)
{
	std::string out = "H\x02\x00""C"s;
	out.push_back((std::uint8_t) method.size());
	out.append(method);
	out.push_back('\x90' + arguments.size());
	return std::move(out);
}

}
