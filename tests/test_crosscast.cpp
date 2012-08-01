// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>

#include <boost/mpl/vector.hpp>


#include "gofvisitor.hpp"
#include "visitable_classes.hpp"

#include "cast.hpp"

struct Derived;

struct Visitable_Classes
    : ::boost::mpl::vector<Derived> 
{};
struct MyVisitor
	: visitor::gofvisitor<MyVisitor,Visitable_Classes>
{};

struct virtual_base
{
	virtual ~virtual_base() {}
	VISITOR_GOFVISITOR_PURE_VIRTUAL_ACCEPT(MyVisitor)
};

VISITOR_GOFVISITOR_NON_MEMBER_ACCEPT(virtual_base,MyVisitor)
VISITOR_CREATE_VISITABLE_CLASSES_TRAIT(virtual_base,Visitable_Classes) 


struct Base_A
	: virtual virtual_base
{};

struct Base_B
	: virtual virtual_base
{};

struct Base_C
	: virtual virtual_base
{};

struct Base_D
{};

struct Derived 
	: Base_A
	, Base_B
	, Base_D
{
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
};

int test_main( int, char *[] )  
{
	Derived D;
	Base_A& A=D;
	Base_B& B=D;
	virtual_base& V=D;
	
    BOOST_CHECK ( 	visitor::cast<Base_A*>(&B)	!= 0							);
    BOOST_CHECK ( 	visitor::cast<Base_B*>(&A)	!= 0							);
	BOOST_CHECK ( 	visitor::cast<Base_A*>(&V)  == 	visitor::cast<Base_A*>(&B)	);
	BOOST_CHECK ( 	visitor::cast<Base_B*>(&V)  == 	visitor::cast<Base_B*>(&A)	);
	
	BOOST_CHECK (	visitor::cast<Base_C*>(&A)	== 0							);
	BOOST_CHECK (	visitor::cast<Base_D*>(&A)	!= 0							);
	
	
	return 0;
}


    


