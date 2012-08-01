#ifndef VISITOR_TESTS_GOF_CLASSES_HPP
#define VISITOR_TESTS_GOF_CLASSES_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/vector.hpp>


#include "gofvisitor.hpp"
#include "visitable_classes.hpp"

struct Derived_A;
struct Derived_B;
struct Derived_A_1;

struct Base_Visitable_Classes
    : ::boost::mpl::vector<Derived_A,Derived_B,Derived_A_1> 
{};
    
struct MyVisitor
	: visitor::gofvisitor<MyVisitor,Base_Visitable_Classes>
{};

struct Base
{
	virtual ~Base() {}
	VISITOR_GOFVISITOR_PURE_VIRTUAL_ACCEPT(MyVisitor)
};

struct Derived_A
	: Base
{
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
};

struct Derived_B
	: Base
{
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
};

struct Derived_A_1
	: Derived_A
{
	char Data[200];
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
};

VISITOR_GOFVISITOR_NON_MEMBER_ACCEPT(Base,MyVisitor)
VISITOR_CREATE_VISITABLE_CLASSES_TRAIT(Base,Base_Visitable_Classes) 


#endif