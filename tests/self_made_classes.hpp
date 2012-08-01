#include "selfmadeclass.hpp"

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

class Base;
class Derived_A;
class Derived_A_1;
class Derived_B;

typedef boost::mpl::vector<Derived_A,Derived_A_1,Derived_B> VisitableClasses;

class Base 
	: public visitor::selfmadeclass<Base,VisitableClasses>
{
protected:
	Base(typeholder t) 
		: visitor::selfmadeclass<Base,VisitableClasses>(t)
	{}
private:
	Base();		
};

class Derived_A
	: public Base
{
public:
	Derived_A() 
		: Base(visitor::type<Derived_A>())
	{}
protected:
	Derived_A(typeholder t)
		: Base(t)
	{}
};

class Derived_A_1
	: public Derived_A
{
public:
	Derived_A_1()
		: Derived_A(visitor::type<Derived_A_1>())
	{}
};

class Derived_B
	: public Base
{
public:
	Derived_B()
		: Base(visitor::type<Derived_B>())
	{}
};
