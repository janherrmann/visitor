// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>

#include <boost/mpl/vector.hpp>

#include "type_holder.hpp"

struct A {};
struct B {};
struct C {};


int test_main( int, char *[] )  
{
	typedef boost::mpl::vector<A,B> types;
	typedef visitor::type_holder<types> 	my_type_holder;
	
	my_type_holder A_=visitor::type<A>();
	my_type_holder B_=visitor::type<B>();
	
	
	BOOST_CHECK	(	A_.id	== 	0	);
	BOOST_CHECK	(	B_.id	== 	1	);
	
	return 0;
}