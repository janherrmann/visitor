// Copyright (c) 2012,2013 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory>

#include "rtti/clone.hpp"

#include "../basic_polymorphic.hpp"


#define BOOST_TEST_MODULE cast
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;


// a few objects for cloning
Derived_A   a;
Base&       ba=a;        
Derived_A_1 a1;
Base&       ba1=a1;
Derived_A_2 a2;
Base&       ba2=a2;
Derived_B   b;
Base&       bb=b;

Unrelated   u;

BOOST_AUTO_TEST_SUITE( clone )

BOOST_AUTO_TEST_CASE ( clone_1 )
{
	using visitor::rtti::clone;
	
	
	Base* b;
	
	b=clone(ba);
	BOOST_CHECK		( typeid(*b) 			== typeid(Derived_A)	);
	BOOST_CHECK		( b						!= &ba					);
	delete b;
	
	
	b=clone(ba1);
	BOOST_CHECK		( typeid(*b) 			== typeid(Derived_A_1)	);
	BOOST_CHECK		( b						!= &ba1					);
	delete b;

	b=clone(ba2);
	BOOST_CHECK		( typeid(*b) 			== typeid(Derived_A_2)	);
	BOOST_CHECK		( b						!= &ba1					);
	delete b;
	
	b=clone(bb);
	BOOST_CHECK		( typeid(*b) 			== typeid(Derived_B)	);
	BOOST_CHECK		( b						!= &bb					);
	delete b;

}

 BOOST_AUTO_TEST_SUITE_END()


