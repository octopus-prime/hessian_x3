/*
 * generator.cpp
 *
 *  Created on: 27.02.2016
 *      Author: mike_gresens
 */

#include <hessian/generator.hpp>
#include "generator/generator_value.hpp"
#include "generator/generator_ref.hpp"
#include "generator/generator_def.hpp"
#include "generator/generator_null.hpp"
#include "generator/generator_bool.hpp"
#include "generator/generator_int.hpp"
#include "generator/generator_long.hpp"
#include "generator/generator_double.hpp"
#include "generator/generator_date.hpp"
#include "generator/generator_string.hpp"
#include "generator/generator_binary.hpp"
#include "generator/generator_list.hpp"
#include "generator/generator_map.hpp"
#include "generator/generator_object.hpp"

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
	std::string call("H\x02\x00""C"s);

	generator::value_visitor visitor(call);
	visitor(method);
	visitor(static_cast<int_t>(arguments.size()));
	for (const auto& argument : arguments)
		boost::apply_visitor(visitor, argument);

	return call;
}

}
