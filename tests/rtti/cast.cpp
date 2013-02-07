// Copyright (c) 2012,2013 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "rtti/cast.hpp"

#include "../basic_polymorphic.hpp"


#define BOOST_TEST_MODULE cast
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;


// a few objects for casting
Derived_A   a;
Base&       ba=a;        
Derived_A_1 a1;
Base&       ba1=a1;
Derived_A_2 a2;
Base&       ba2=a2;
Derived_B   b;
Base&       bb=b;

Unrelated   u;

BOOST_AUTO_TEST_SUITE( cast )

BOOST_AUTO_TEST_CASE ( cast_1 )
{
	BOOST_CHECK 		(	visitor::rtti::cast<Derived_A*>(&ba) 	!=	0						);
	BOOST_CHECK 		(	visitor::rtti::cast<Derived_A*>(&ba1)	!=	0						);
	
	BOOST_CHECK			(	visitor::rtti::cast<Derived_A*>(&bb)	==	0						);
	BOOST_CHECK 		(	visitor::rtti::cast<Unrelated*>(&ba)	==	0						);
	
	BOOST_CHECK			(	&visitor::rtti::cast<Derived_A_1&>(ba1)	==	&a1						);
	
	BOOST_CHECK_THROW	(	visitor::rtti::cast<Derived_A_1&>(ba)	,	std::bad_cast			);
	
	
	

}

 BOOST_AUTO_TEST_SUITE_END()


