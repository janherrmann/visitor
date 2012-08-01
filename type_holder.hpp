#ifndef VISITOR_TYPE_HOLDER
#define VISITOR_TYPE_HOLDER

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "type.hpp"

// class type_holder maps an type to an integral id eaqual 
// to the position in a mpl foreward sequence
// it is only copy construct able and constructable from  
// visitor::type<T> when T is in the typelist

namespace visitor {

	template<class sequence_,class integral_type_holder_=std::size_t>
	class type_holder
	{	
	public:
		typedef integral_type_holder_ 	integral_type_holder;
		typedef sequence_				sequence;
		
		template<class T>
		type_holder(type<T>, typename enable_if_contains<sequence,T>::type* dummy=0)
            : id(type_pos<sequence,T>::value)
        {}
		
		integral_type_holder const id;

	private:
		type_holder();
	};

} // NS visitor

#endif