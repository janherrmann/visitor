#ifndef BASIC_POLYMORPHIC_HPP
#define BASIC_POLYMORPHIC_HPP

// Copyright (c) 2013 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// single inheritance hierarchy for simple test cases

#include <boost/mpl/vector.hpp>

#include "gofvisitor.hpp"

struct Base;
struct Derived_A;
struct Derived_B;
struct Derived_A_1;
struct Derived_A_2;

struct Unrelated;

struct Base_Visitable_Classes
    : ::boost::mpl::vector<Derived_A,Derived_B,Derived_A_1,Derived_A_2> 
{};

struct MyVisitor
	: visitor::gofvisitor<MyVisitor,Base_Visitable_Classes>
{};

struct Base {
	virtual ~Base() {}
	
	VISITOR_GOFVISITOR_PURE_VIRTUAL_ACCEPT(MyVisitor)
};

VISITOR_GOFVISITOR_NON_MEMBER_ACCEPT(Base,MyVisitor)



struct Derived_A
	: Base
{
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
};

struct Derived_A_1
	: Derived_A
{
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
	char Data[10];
};

struct Derived_A_2
	: Derived_A
{
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
	char Data[50];
};


struct Derived_B
	: Base
{
	VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(MyVisitor)
	char Data[10];
};

struct Unrelated
{};


#endif