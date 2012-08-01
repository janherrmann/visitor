// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>

#include <boost/utility/enable_if.hpp>

#include "gof_classes.hpp"

int const A=1;
int const B=2;
int const A1=3;
int const A_C=4;
int const B_C=5;
int const A1_C=6;


// simply identifying some objects 
// const and non-const 
struct test_visitor 
{
	std::size_t result;
	void operator()(Derived_A const&) {
		result=A_C;
	}
	
	void operator()(Derived_B const&) {
		result=B_C;
	}

	void operator()(Derived_A_1 const&) {
		result=A1_C;
	}
	
	void operator()(Derived_A&) {
		result=A;
	}
	
	void operator()(Derived_B&) {
		result=B;
	}

	void operator()(Derived_A_1&) {
		result=A1;
	}
}; // test_visitor

std::size_t test_it(Base const& b) {
	test_visitor v;
	accept(b, v);
	return v.result;
}

std::size_t test_it(Base& b) {
	test_visitor v;
	accept(b, v);
	return v.result;
}

// checks runtimme(like)  polymorphism (simple derived to base conversation)
struct is_A_visitor 
{
	bool result;

	void operator()(Derived_A const&) {
		result=true;
	}
	
	void operator()(Base const&) {
	}
	is_A_visitor() : result(false) {}
}; 

bool is_A(Base const& b) {
	is_A_visitor v;
	accept(b, v);
	return v.result;
}


// checks compile time polymorphism
struct is_small_visitor
{
	bool result;
    template<class T>
    typename ::boost::enable_if_c<(sizeof(T)<100)>::type operator()(T const&)
    {
		result=true;
	}

	template<class T>
	typename ::boost::enable_if_c<!(sizeof(T)<100)>::type operator()(T const&)
	{
		result=false;
	}
};

bool is_small(Base const& obj) {
	is_small_visitor v;
    accept(obj, v);
    return v.result;
}

int test_main( int, char *[] )  
{
	Derived_A 	a;
	Derived_B 	b;
	Derived_A_1 a1;
	Base&		ba=a;
	Base&		bb=b;
	Base&		ba1=a1;
	
	Base const&	cba=a;
	Base const& cbb=b;
	Base const& cba1=a1;
	
	BOOST_CHECK	(	test_it(ba)				==	A					);
	BOOST_CHECK	(	test_it(cba)			==	A_C					);
	BOOST_CHECK	(	test_it(bb)				==	B					);
	BOOST_CHECK	(	test_it(cbb)			==	B_C					);
	BOOST_CHECK	(	test_it(ba1)			==	A1					);
	BOOST_CHECK	(	test_it(cba1)			==	A1_C				);
	
	BOOST_CHECK	(	is_A(cba)	);
	BOOST_CHECK (	is_A(cba1)	);
	BOOST_CHECK	( ! is_A(cbb)	);
	
	BOOST_CHECK	(	is_small(cba)	);
	BOOST_CHECK	(	is_small(cbb)	);
	BOOST_CHECK	( ! is_small(cba1)	);
	
	return 0;
}




