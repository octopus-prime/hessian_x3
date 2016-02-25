/*
 * parser.cpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#include <hessian/parser.hpp>
#include "parser/parser_value_fwd.hpp"
#include "parser/parser_byte.hpp"
#include "parser/parser_null.hpp"
#include "parser/parser_bool.hpp"
#include "parser/parser_int.hpp"
#include "parser/parser_long.hpp"
#include "parser/parser_double.hpp"
#include "parser/parser_date.hpp"
#include "parser/parser_string.hpp"
#include "parser/parser_binary.hpp"
#include "parser/parser_type.hpp"
#include "parser/parser_def.hpp"
#include "parser/parser_ref.hpp"
#include "parser/parser_list.hpp"
#include "parser/parser_map.hpp"
#include "parser/parser_object.hpp"
#include "parser/parser_value.hpp"
#include "parser/parser_content.hpp"

namespace hessian {

const char*
parse_exception::what() const noexcept
{
	return "Parsing failed.";
}

content_t
parse(std::string&& stream)
{
	std::string::const_iterator begin(stream.begin()), end(stream.end());
	parser::def_t def;
	parser::ref_t ref;
	const auto rule = x3::with<parser::def_tag>(std::ref(def)) [ x3::with<parser::ref_tag>(std::ref(ref)) [parser::content_rule] ];
	content_t content;

	const bool ok = x3::parse(begin, end, rule, content);
	if (!ok || begin != end)
		throw parse_exception();

	return std::move(content);
}

}
