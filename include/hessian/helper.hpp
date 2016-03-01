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
inline T
get(const value_t& value);

template <typename T>
inline value_t
set(const T& value);

namespace detail {

template <typename T> struct is_value : std::false_type { };
template <> struct is_value<null_t> : std::true_type { };
template <> struct is_value<bool_t> : std::true_type { };
template <> struct is_value<int_t> : std::true_type { };
template <> struct is_value<long_t> : std::true_type { };
template <> struct is_value<double_t> : std::true_type { };
template <> struct is_value<date_t> : std::true_type { };
template <> struct is_value<string_t> : std::true_type { };
template <> struct is_value<binary_t> : std::true_type { };

template <typename T> struct is_optional : std::false_type { };
template <typename... Ts> struct is_optional<boost::optional<Ts...> > : std::true_type { };

template <typename T> struct is_list : std::false_type { };
template <typename... Ts> struct is_list<std::vector<Ts...> > : std::true_type { };

template <typename T> struct is_map : std::false_type { };
template <typename... Ts> struct is_map<std::unordered_map<Ts...> > : std::true_type { };

template <typename T, typename Enable = void>
struct converter {};

template <typename T>
struct converter<T, typename std::enable_if_t<is_value<T>::value>>
{
	static const T& from(const value_t& value)
	{
		return boost::get<T>(value);
	}

	static value_t to(const T& value)
	{
		return value;
	}
};

template <typename T>
struct converter<T, typename std::enable_if_t<is_optional<T>::value>>
{
	static T from(const value_t& value)
	{
		return boost::apply_visitor(optional_visitor(), value);
	}

	static value_t to(const T& value)
	{
		return value ? value_t(value.get()) : value_t(null_t());
	}

private:
	struct optional_visitor : boost::static_visitor<T>
	{
		template <typename U>
		T operator()(const U& value) const
		{
			throw std::bad_cast();
		}

		T operator()(const null_t& value) const
		{
			return T();
		}

		T operator()(const T& value) const
		{
			return T(value);
		}
	};
};

template <typename T>
struct converter<T, typename std::enable_if_t<is_list<T>::value>>
{
	static T from(const value_t& value)
	{
		T list;
		for (const auto& element : boost::get<list_t>(value))
			list.push_back(get<typename T::value_type>(element));
		return std::move(list);
	}

	static value_t to(const T& value)
	{
		list_t list;
		for (const auto& element : value)
			list.push_back(set(element));
		return std::move(list);
	}
};

template <typename T>
struct converter<T, typename std::enable_if_t<is_map<T>::value>>
{
	static T from(const value_t& value)
	{
		T map;
		for (const auto& element : boost::get<map_t>(value))
			map.emplace(get<typename T::key_type>(element.first), get<typename T::mapped_type>(element.second));
		return std::move(map);
	}

	static value_t to(const T& value)
	{
		map_t map;
		for (const auto& element : value)
			map.emplace(set(element.first), set(element.second));
		return std::move(map);
	}
};

}

template <typename T>
inline T
get(const value_t& value)
{
	return detail::converter<T>::from(value);
}

template <typename T>
inline value_t
set(const T& value)
{
	return detail::converter<T>::to(value);
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
	const object_t& object = boost::get<object_t>(value); \
	return STRUCT_NAME \
	{ \
		BOOST_PP_SEQ_FOR_EACH_I(GET, STRUCT_NAME, SEQ) \
	}; \
}\
}

#define SET(r, type, i, member) BOOST_PP_COMMA_IF(i) \
{BOOST_PP_STRINGIZE(member), set(value.member)}

#define DEFINE_SET(STRUCT_NAME, SEQ) \
namespace hessian { \
template <> \
value_t \
set(const STRUCT_NAME& value) \
{ \
	return object_t \
	{ \
		BOOST_PP_SEQ_FOR_EACH_I(SET, _, SEQ) \
	}; \
}\
}
