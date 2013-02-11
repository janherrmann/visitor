// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <memory>

#include <boost/test/minimal.hpp>


#include <boost/utility/enable_if.hpp>

#include "gof_classes.hpp"
#include "type_id.hpp"

#include "rtti/cast.hpp"
#include "rtti/clone.hpp"


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
	
	visitor::type_id<Base> id_empty;  
    visitor::type_id<Base> id_a=visitor::type<Derived_A>();
    visitor::type_id<Base> id_a_(0); 
    visitor::type_id<Base> id_a1=visitor::type<Derived_A_1>();
    visitor::type_id<Base> id_b=visitor::type<Derived_B>();
	
	BOOST_CHECK (   id_a.get_type_id()			==  0           );
	BOOST_CHECK (	id_a_.get_type_id()			==	0			);
	BOOST_CHECK (	id_a						== 	id_a		);
	BOOST_CHECK (	id_a						== 	id_a_		);
	
	BOOST_CHECK	(	id_b.get_type_id()			== 	1			);
	BOOST_CHECK (	id_a1.get_type_id()			==	2			);
	
	BOOST_CHECK (	id_a						<= 	id_a		);
	BOOST_CHECK	( 	id_a						<= 	id_b		);
	BOOST_CHECK	(	id_a						<	id_b		);
	BOOST_CHECK	(	id_b						<	id_a1		);
	BOOST_CHECK	(	id_a1						<	id_empty	);
	
	BOOST_CHECK	( !	id_a.is_empty()								);
	BOOST_CHECK	( !	id_b.is_empty()								);
	BOOST_CHECK	( !	id_a1.is_empty()							);
	BOOST_CHECK	(	id_empty.is_empty()							);
	
    BOOST_CHECK (   visitor::identify(cba)      ==  id_a        );
    BOOST_CHECK (   visitor::identify(cba1)     ==  id_a1       );
    BOOST_CHECK (   visitor::identify(cbb)      ==  id_b        );

	BOOST_CHECK (   type_info_(id_a)            ==  typeid(Derived_A)   );
    BOOST_CHECK (   type_info_(id_empty)        ==  typeid(void)    	);

	
    BOOST_CHECK (   sizeof_(id_empty)           ==  0                   );
    BOOST_CHECK (   sizeof_(id_a)               ==  sizeof(Derived_A)   );
    BOOST_CHECK (   sizeof_(id_b)               ==  sizeof(Derived_B)   );
    BOOST_CHECK (   sizeof_(id_a1)              ==  sizeof(Derived_A_1) );
	

    boost::shared_ptr<Base> nulltype(create_(id_empty));
    boost::shared_ptr<Base> create_a(create_(id_a));
    boost::shared_ptr<Base> create_b(create_(id_b));
    boost::shared_ptr<Base> create_a1(create_(id_a1));

    BOOST_CHECK (   nulltype                    ==  0                           );
    BOOST_CHECK (   create_a                    !=  0                           );
    BOOST_CHECK (   create_b                    !=  0                           );
    BOOST_CHECK (   create_a1					!=  0                           );

    BOOST_CHECK (   typeid(*create_a)           ==  typeid(Derived_A)           );
    BOOST_CHECK (   typeid(*create_b)           ==  typeid(Derived_B)           );
    BOOST_CHECK (   typeid(*create_a1)          ==  typeid(Derived_A_1)         );
	

    BOOST_CHECK ( visitor::rtti::cast<Derived_A*>(&ba)      !=  0                       );
    BOOST_CHECK ( visitor::rtti::cast<Derived_A*>(&ba1)     !=  0                       );
    BOOST_CHECK ( visitor::rtti::cast<Derived_A*>(&bb)      ==  0                       );

    BOOST_CHECK ( & visitor::rtti::cast<Derived_A&>(ba)     !=  0                       );

    //BOOST_CHECK_THROW ( visitor::cast<Derived_A&>(bb)       ,   std::bad_cast           );

	id_a=visitor::type<Derived_A>();

    
	std::auto_ptr<Base>         cloned_ba(visitor::rtti::clone<Base>(cba));
	std::auto_ptr<Derived_A>    cloned_da(visitor::rtti::clone<Derived_A>(a));

    BOOST_CHECK (   cloned_ba.get()                         !=  0               );
    BOOST_CHECK (   visitor::identify<Base>(*cloned_ba)     ==  id_a            );
    BOOST_CHECK (   cloned_ba.get()                         !=  &ba             );

    BOOST_CHECK (   cloned_da.get()                         !=  0               );
    BOOST_CHECK (   visitor::identify<Base>(*cloned_da)     ==  id_a            );
    BOOST_CHECK (   cloned_da.get()                         !=  &a              );


	return 0;
}




