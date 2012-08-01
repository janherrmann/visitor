#ifndef VISITOR_TYPE_HPP
#define VISITOR_TYPE_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/find.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace visitor {

    // represents a type
	
	template<class T>
	struct type {};
	
	template<class sequence,class T>
	struct type_pos
		: boost::mpl::find<sequence,T>::type::pos
	{};
	
	template<class sequence,class T>
	struct enable_if_contains
		: boost::enable_if<boost::mpl::contains<sequence,T> >
	{};
	

} // NS visitor

#endif