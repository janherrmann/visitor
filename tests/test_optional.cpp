// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>

#include <boost/optional.hpp>

#include "accept_optional.hpp"

struct is_neg_visitor 
{
	bool result;
	
	template<class T>
	void operator()(T const& obj) 
	{
		result=(obj<0);
	}
	
	void operator()(visitor::empty_optional)
	{
		result=false;
	}
};

template<class T>
bool is_neg(boost::optional<T> const& obj) 
{
	using namespace visitor;
	is_neg_visitor v;
	accept(obj, v);
	return v.result; 
}

int test_main( int, char *[] )  
{
	boost::optional<int> i_pos=3;
	boost::optional<int> i_null=0;
	boost::optional<int> i_neg=-3;
	boost::optional<int> i_nothing;
	boost::optional<double> d_pos=2.4;
	boost::optional<double> d_neg=-2.3;
	boost::optional<double> d_nothing;
	
	BOOST_CHECK ( !	is_neg(i_pos)		);
	BOOST_CHECK ( !	is_neg(i_null)		);
	BOOST_CHECK ( 	is_neg(i_neg)		);
	BOOST_CHECK ( !	is_neg(i_nothing)	);
	BOOST_CHECK ( !	is_neg(d_pos)		);
	BOOST_CHECK ( 	is_neg(d_neg)		);
	BOOST_CHECK ( !	is_neg(d_nothing)	);
	
	return 0;
}




