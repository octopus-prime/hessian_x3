/*
 * helper.hpp
 *
 *  Created on: 29.02.2016
 *      Author: mike_gresens
 */

#pragma once

#include <hessian/value.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

namespace hessian {

template <typename T>
struct optioal_visitor : boost::static_visitor<boost::optional<T>>
{
	template <typename U>
	boost::optional<T> operator()(const U& value) const
	{
		throw std::bad_cast();
	}

	boost::optional<T> operator()(const null_t& value) const
	{
		return boost::optional<T>();
	}

	boost::optional<T> operator()(const T& value) const
	{
		return boost::optional<T>(value);
	}
};

template <typename T>
T
get(const value_t& value);

template <>
inline bool_t
get(const value_t& value)
{
	return boost::get<bool_t>(value);
}

template <>
inline int_t
get(const value_t& value)
{
	return boost::get<int_t>(value);
}

template <>
inline long_t
get(const value_t& value)
{
	return boost::get<long_t>(value);
}

template <>
inline double_t
get(const value_t& value)
{
	return boost::get<double_t>(value);
}

template <>
inline date_t
get(const value_t& value)
{
	return boost::get<date_t>(value);
}

template <>
inline string_t
get(const value_t& value)
{
	return boost::get<string_t>(value);
}

template <>
inline binary_t
get(const value_t& value)
{
	return boost::get<binary_t>(value);
}

template <>
inline list_t
get(const value_t& value)
{
	return boost::get<list_t>(value);
}

template <>
inline map_t
get(const value_t& value)
{
	return boost::get<map_t>(value);
}

template <>
inline object_t
get(const value_t& value)
{
	return boost::get<object_t>(value);
}

template <>
inline boost::optional<bool_t>
get(const value_t& value)
{
	return boost::apply_visitor(optioal_visitor<bool_t>(), value);
}

template <>
inline boost::optional<date_t>
get(const value_t& value)
{
	return boost::apply_visitor(optioal_visitor<date_t>(), value);
}

template <>
inline boost::optional<object_t>
get(const value_t& value)
{
	return boost::apply_visitor(optioal_visitor<object_t>(), value);
}

}

#define GET(r, type, i, member) BOOST_PP_COMMA_IF(i) \
get<decltype(type::member)>(object.at(BOOST_PP_STRINGIZE(member)))

#define DEFINE_GET(STRUCT_NAME, SEQ) \
namespace hessian { \
template <> \
STRUCT_NAME \
get<STRUCT_NAME>(const value_t& value) \
{ \
	const object_t& object = get<object_t>(value); \
	return STRUCT_NAME \
	{ \
		BOOST_PP_SEQ_FOR_EACH_I(GET, STRUCT_NAME, SEQ) \
	}; \
}\
}
