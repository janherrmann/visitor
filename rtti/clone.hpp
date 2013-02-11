#ifndef VISITOR_RTTI_CLONE_HPP
#define VISITOR_RTTI_CLONE_HPP

// Copyright (c) 2012,2013 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/mpl/logical.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/utility/addressof.hpp>


#include <iostream>


namespace visitor { namespace rtti {

    namespace impl {
	
        template <class Target>
        struct clone_visitor 
        {
            Target* result;

			clone_visitor()
                : result(0)
            {}

			
			template<class T>
			struct enable_helper : 	
				boost::mpl::and_<
					boost::mpl::not_<boost::is_abstract<T> >,
					boost::is_base_of<Target,T>
				>
			{};
			
			template<class T>
			typename boost::enable_if<enable_helper<T> >::type 
			operator()(T const& obj) 
			{
				result=new T(obj);
			}

			template<class T>
			typename boost::disable_if<enable_helper<T> >::type 
			operator()(T const& obj)
			{
				// abstract classes and classes not
				// derived from target have an empty 
				// implementation 
			}			
        }; // struct clone_visitor
    } // NS impl

    template<class T>
    T* clone(T const& obj)
    {
        impl::clone_visitor<T> sv;
        accept(obj, sv);
        return sv.result;
    }

}} // NS visitor::rtti

#endif
