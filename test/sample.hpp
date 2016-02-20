/*
 * sample.hpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#pragma once

#include <boost/algorithm/hex.hpp>
#include <sstream>

using namespace std::literals;

namespace hessian {

template <typename T>
using sample_t = std::pair<std::string, T>;

template <typename T>
using samples_t = std::vector<sample_t<T>>;

}

namespace std {

template <typename T>
inline ostream&
operator<<(ostream& stream, const hessian::sample_t<T>& sample)
{
	stream << boost::algorithm::hex(sample.first) << " & " << hessian::value_t(sample.second);
	return stream;
}

}
