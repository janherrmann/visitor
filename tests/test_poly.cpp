// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>

#include <boost/any.hpp>
#include <boost/mpl/vector.hpp>

#include "ad_hoc/poly.hpp"

struct Base {
	virtual ~Base() {}
};

struct Derived_A
	: Base
{};
struct Derived_A_1
	: Derived_A
{};
struct Derived_B
	: Base
{};

struct is_B_visitor {
	bool result;
	is_B_visitor()
		: result(false)
	{}
	
	void operator()(Derived_B const&)
	{
		result=true;
	}
	
	template<class T>
	void operator()(T const&)
	{}
};
	
struct is_A_visitor {
		bool result;
		is_A_visitor()
			: result(false)
		{}
		
		void operator()(Derived_A const&) 
		{   
			result=true;
		}
		
		void operator()(Base const&)
		{
			result=false;
		}
};

#include <iostream>

struct is_non_const_A1_visitor {
	bool result;
	void operator()(Derived_A_1&) {
		result=true;
	}

	void operator()(Base&) {
		result=false;
	}
};

template<class T>
bool is_A(T const& b) {
	is_A_visitor v;
	accept(b,v);
	return v.result;
}
template<class T>
bool is_B(T const& b) {
	is_B_visitor v;
	accept(b,v);
	return v.result;
}

template<class T>
bool is_non_const_A1(T b) {
	is_non_const_A1_visitor v;
	accept(b,v);
	return v.result;
}
int test_main( int, char *[] )  
{
	Derived_A a;
	Derived_A_1 a1;
	Derived_B b;
	
	Base& ba=a;
	Base& ba1=a1;
	Base& bb=b;
	
	Base const& cba=a;
	Base const& cbb=b;
	Base const& cba1=a1;
	
	typedef boost::mpl::vector<Derived_A,Derived_B,Derived_A_1> Visittypes1;
	typedef boost::mpl::vector<Derived_B,Derived_A,Derived_A_1> Visittypes2;
	typedef boost::mpl::vector<Derived_A_1,Derived_A,Derived_B> Visittypes3;
	
	using namespace visitor::ad_hoc::poly; // for warp, c_wrap
	

	BOOST_CHECK	(	is_A(c_wrap<Visittypes1>(cba))				);	
	BOOST_CHECK	(	is_A(wrap<Visittypes1>(cba))				);	
	BOOST_CHECK	(	is_A(wrap<Visittypes1>(ba))					);	
	BOOST_CHECK	(	is_A(c_wrap<Visittypes1>(cba1))				);	
	BOOST_CHECK	( !	is_A(c_wrap<Visittypes1>(cbb))				);	
	BOOST_CHECK	( !	is_A(wrap<Visittypes1>(cbb))				);	
	BOOST_CHECK	( !	is_A(wrap<Visittypes1>(bb))					);	
	
	BOOST_CHECK	( !	is_B(c_wrap<Visittypes1>(cba))				);	
	BOOST_CHECK	( !	is_B(wrap<Visittypes1>(cba))				);	
	BOOST_CHECK	( !	is_B(wrap<Visittypes1>(ba))					);	
	BOOST_CHECK	( !	is_B(c_wrap<Visittypes1>(cba1))				);	
	BOOST_CHECK	( 	is_B(c_wrap<Visittypes1>(cbb))				);	
	BOOST_CHECK	( 	is_B(wrap<Visittypes1>(cbb))				);	
	BOOST_CHECK	( 	is_B(wrap<Visittypes1>(bb))					);
	
	
	BOOST_CHECK ( ! is_non_const_A1(wrap<Visittypes1>(ba))		);	
	BOOST_CHECK ( ! is_non_const_A1(wrap<Visittypes1>(bb))		);	
	BOOST_CHECK (   is_non_const_A1(wrap<Visittypes1>(ba1))		);	

	
	BOOST_CHECK ( ! is_non_const_A1(wrap<Visittypes2>(ba))		);	
	BOOST_CHECK ( ! is_non_const_A1(wrap<Visittypes2>(bb))		);	
	BOOST_CHECK (   is_non_const_A1(wrap<Visittypes2>(ba1))		);	

	BOOST_CHECK ( ! is_non_const_A1(wrap<Visittypes3>(ba))		);	
	BOOST_CHECK ( ! is_non_const_A1(wrap<Visittypes3>(bb))		);	
	BOOST_CHECK (   is_non_const_A1(wrap<Visittypes3>(ba1))		);	

	return 0;
}




