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

namespace detail {

struct native_tag;
struct optional_tag;
struct list_tag;
struct object_tag;

template <typename T, typename Tag>
struct getter;

template <typename T>
struct getter<T, native_tag>
{
	const T& operator()(const value_t& value) const
	{
		return boost::get<T>(value);
	}
};

template <typename T>
struct getter<T, optional_tag>
{
	boost::optional<T> operator()(const value_t& value) const
	{
		return boost::apply_visitor(optional_visitor(), value);
	}

private:
	struct optional_visitor : boost::static_visitor<boost::optional<T>>
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
};

template <typename T>
struct getter<T, list_tag>
{
	std::vector<T> operator()(const value_t& value) const
	{
		const list_t& list1 = boost::get<list_t>(value);
		std::vector<T> list2;
		std::transform(list1.begin(), list1.end(), std::back_inserter(list2), get<T>);
		return std::move(list2);
	}
};

template <typename T>
struct getter_traits
{
	typedef getter<T, native_tag> type;
};

template <typename T>
struct getter_traits<boost::optional<T>>
{
	typedef getter<T, optional_tag> type;
};

template <typename T>
struct getter_traits<std::vector<T>>
{
	typedef getter<T, list_tag> type;
};

}

template <typename T>
inline T
get(const value_t& value)
{
	typedef typename detail::getter_traits<T>::type getter;
	return getter()(value);
}

/*
template <typename T>
T
get(const value_t& value);

template <>
inline null_t
get(const value_t& value)
{
	return boost::get<null_t>(value);
}

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
	return boost::apply_visitor(optional_visitor<bool_t>(), value);
}

template <>
inline boost::optional<int_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<int_t>(), value);
}

template <>
inline boost::optional<long_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<long_t>(), value);
}

template <>
inline boost::optional<double_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<double_t>(), value);
}

template <>
inline boost::optional<date_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<date_t>(), value);
}

template <>
inline boost::optional<string_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<string_t>(), value);
}

template <>
inline boost::optional<binary_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<binary_t>(), value);
}

template <>
inline boost::optional<list_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<list_t>(), value);
}

template <>
inline boost::optional<map_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<map_t>(), value);
}

template <>
inline boost::optional<object_t>
get(const value_t& value)
{
	return boost::apply_visitor(optional_visitor<object_t>(), value);
}
*/
template <typename T>
value_t
set(const T& value);

template <>
inline value_t
set(const bool& value)
{
	return value;
}

template <>
inline value_t
set(const std::int32_t& value)
{
	return value;
}

template <>
inline value_t
set(const std::string& value)
{
	return value;
}

template <>
inline value_t
set(const boost::optional<std::string>& value)
{
	return value ? value_t(value.get()) : value_t(null_t());
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

#define SET(r, type, i, member) BOOST_PP_COMMA_IF(i) \
{BOOST_PP_STRINGIZE(member), value.member}

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
