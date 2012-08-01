// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>


#include <boost/variant.hpp>

#include "accept_variant.hpp"

struct is_int_visitor {
	bool result;
	void operator()(int) {
		result=true;
	}
	
	template<class T>
	void operator()(T const&) {
		result=false;
	}
};

struct is_float_visitor {
	bool result;
	void operator()(float) {
		result=true;
	}
	
	template<class T>
	void operator()(T const&) {
		result=false;
	}
};

template<class T>
bool is_int(T const& obj)
{
	is_int_visitor sv;
	visitor::accept(obj, sv);
	return sv.result;
}

template<class T>
bool is_float(T const& obj)
{
	is_float_visitor sv;
	visitor::accept(obj, sv);
	return sv.result;
}



int test_main( int, char *[] )  
{
	boost::variant<float, int, char const*> var=0.0f;
	
	BOOST_CHECK (	is_float(var)	);
	BOOST_CHECK ( ! is_int(var)		);
	
	var=1;
	BOOST_CHECK ( ! is_float(var)	);
	BOOST_CHECK ( 	is_int(var)		);
	
	var = "abc";
	BOOST_CHECK ( ! is_float(var)	);
	BOOST_CHECK ( ! is_int(var)		);
		
	return 0;
}




