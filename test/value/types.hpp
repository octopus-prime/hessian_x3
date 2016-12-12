/*
 * types.hpp
 *
 *  Created on: 12.12.2016
 *      Author: mgresens
 */

#pragma once

#include <hessian/value.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/remove.hpp>

namespace mpl = boost::mpl;

namespace hessian {

typedef mpl::vector
<
	null_t,
	bool_t,
	int_t,
	long_t,
	double_t,
	date_t,
	string_t,
	binary_t,
	list_t,
	map_t,
	object_t
>::type all_types;

}
