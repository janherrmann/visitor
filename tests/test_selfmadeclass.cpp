// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/vector.hpp>

#include "self_made_classes.hpp"


struct is_A_visitor {
	bool result;
	
	void operator()(Derived_A const&) { result=true; }
	void operator()(Base const&) { result=false; }
};

bool is_A(Base const& obj) {
	is_A_visitor v;
	accept(obj, v);
	return v.result;
}

int test_main( int, char *[] )  
{
	Derived_A a;
	Derived_A_1 a1;
	Derived_B b;
	
	Base const& cba=a;
	Base const& cbb=b;
	Base const& cba1=a1;
	
	BOOST_CHECK	(	is_A(cba)	);
	BOOST_CHECK	( !	is_A(cbb)	);
	BOOST_CHECK (	is_A(cba1)	); 	

	return 0;
}

