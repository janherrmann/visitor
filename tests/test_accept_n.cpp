// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>

#include <boost/test/minimal.hpp>


#include "gof_classes.hpp"
#include "accept_n.hpp"

struct A_and_B_visitor 
{
	bool result;
	void operator()(Derived_A const& a, Derived_B const& b) {
		result=true;
	}
	
	void operator()(Base const&, Base const&) {
		result=false;
	}
};

bool A_and_B(Base const& l, Base const& r)
{
	A_and_B_visitor sv;
	visitor::accept_2(l, r, sv);
	return sv.result;
}

int test_main( int, char *[] )  
{
	Derived_A 	a;
	Derived_B 	b;
	Derived_A_1 a1;
		
	Base const&	cba=a;
	Base const& cbb=b;
	Base const& cba1=a1;
	
	BOOST_CHECK (	A_and_B(cba, cbb)	);
	BOOST_CHECK	(	A_and_B(cba1, cbb)	);
	
	BOOST_CHECK ( ! A_and_B(cba, cba)	);
	BOOST_CHECK ( ! A_and_B(cbb, cba1)	);
	
	return 0;
}




