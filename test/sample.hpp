/*
 * sample.hpp
 *
 *  Created on: 30.01.2016
 *      Author: mike_gresens
 */

#pragma once

template <typename T>
using sample_t = std::pair<std::string, T>;

template <typename T>
using samples_t = std::vector<sample_t<T>>;

namespace std {

template <typename T>
inline ostream&
operator<<(ostream& stream, const sample_t<T>& sample)
{
	stream << sample.first << " & " << sample.second;
	return stream;
}

}
