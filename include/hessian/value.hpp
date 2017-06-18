/*
 * value.hpp
 *
 *  Created on: 19.02.2016
 *      Author: mgresens
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <iostream>

namespace hessian {

class value_t;
using null_t = std::nullptr_t;
using bool_t = bool;
using int_t = std::int32_t;
using long_t = std::int64_t;
using double_t = double;
using date_t = std::chrono::milliseconds;
using string_t = std::string;
using binary_t = std::basic_string<std::uint8_t>;
using list_t = std::vector<value_t>;
using map_t = std::map<value_t, value_t>;
using object_t = std::map<string_t, value_t>;

inline constexpr null_t null {nullptr};

class value_t
{
public:
	value_t() noexcept
	:
		_variant{null}
	{
	}

	template <typename T>
	value_t(T const& value) noexcept
	:
		_variant{value}
	{
	}

	template <typename T>
	value_t(T& value) noexcept // FIXME: WTF?!
	:
		_variant{value}
	{
	}

	template <typename T>
	value_t(T&& value) noexcept
	:
		_variant{std::move(value)}
	{
	}

	value_t(value_t const& value) = default;
	value_t(value_t& value) = default; // FIXME: WTF?!
	value_t(value_t&& value) = default;

	value_t& operator=(value_t const& value) = default;
	value_t& operator=(value_t&& value) = default;

	template <typename T>
	bool is() const noexcept
	{
		return std::holds_alternative<T>(_variant);
	}

	template <typename T>
	T const& as() const
	{
		return std::get<T>(_variant);
	}

	auto visit(auto&& visitor) const
	{
		return std::visit(std::move(visitor), _variant);
	}

	operator bool() const noexcept
	{
		return !is<null_t>();
	}

	bool operator==(value_t const& value) const
	{
		return _variant == value._variant;
	}

	bool operator<(value_t const& value) const
	{
		return _variant < value._variant;
	}

private:
	std::variant<null_t, bool_t, int_t, long_t, double_t, date_t, string_t, binary_t, list_t, map_t, object_t> _variant;
};

std::ostream& operator<<(std::ostream& stream, const value_t& value);

}
