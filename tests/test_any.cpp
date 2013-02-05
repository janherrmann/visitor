// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/minimal.hpp>
#include <iostream>

#include <boost/any.hpp>
#include <boost/mpl/vector.hpp>

#include "ad_hoc/any.hpp"

struct is_int_visitor {
	bool result;
	void operator()(int const& i) {
		result=true;
	}
	
	is_int_visitor() 
		: result(false)
	{}
	
	template<class T>
	void operator()(T const&) 
	{
		result=false;
	}
	
};

struct is_float_visitor {
	bool result;
	void operator()(float const& f) {
		result=true;
	}
	
	template<class T>
	void operator()(T const&) 
	{
		result=false;
	}
	
	is_float_visitor() 
		: result(false)
	{}
};

struct twice_visitor {
	template<class T>
	void operator()(T& obj) 
	{
		obj*=2;
	}
};

template<class T>
bool is_int(T const& obj)
{
	is_int_visitor sv;
	accept(obj, sv);
	return sv.result;
}

template<class T>
bool is_float(T const& obj)
{
	is_float_visitor sv;
	accept(obj, sv);
	return sv.result;
}

template<class T>
void twice(T obj)
{
	twice_visitor sv;
	accept(obj, sv);
}



int test_main( int, char *[] )  
{
	boost::any amy(4);
	
	using namespace visitor::ad_hoc::any;
	typedef boost::mpl::vector<int,float> anytypes;
		
	BOOST_CHECK ( !	is_float(wrap<anytypes>(amy))				);
	BOOST_CHECK	( 	is_int(wrap<anytypes>(amy))					);

	BOOST_CHECK ( !	is_float(c_wrap<anytypes>(amy))				);
	BOOST_CHECK	( 	is_int(c_wrap<anytypes>(amy))				);
	
	amy=4.f;
	BOOST_CHECK ( 	is_float(wrap<anytypes>(amy))				);
	BOOST_CHECK ( !	is_int(wrap<anytypes>(amy))					);
	
	
	char const* str="amy";
	amy=str;
	BOOST_CHECK ( !	is_float(wrap<anytypes>(amy))				);
	BOOST_CHECK ( !	is_int(wrap<anytypes>(amy))					);
	
	amy=2;
	twice(wrap<anytypes>(amy));
	BOOST_CHECK (   boost::any_cast<int>(amy)		==	4		);
	
	amy=4.f;
	twice(wrap<anytypes>(amy));
	BOOST_CHECK (	boost::any_cast<float>(amy)		==	4.f*2	);
	
	return 0;
}




