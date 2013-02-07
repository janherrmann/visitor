#ifndef VISITOR_CAST_HPP
#define VISITOR_CAST_HPP

// Copyright (c) 2012, 2013 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/*
	Implements an cast operation for visitable types. 
	This operation does not depend on rtti of the c++-runtime!
	This operation has the same complexity as one accept 
	operation (normaly O(1)).
 
	Usage:
		from From;
		to& To=visitor::rtti::cast<to&>(From);
		
		from* From= ... ;
		to* To=visitor::rtti::cast<to*>(From);
	
*/

#include <typeinfo>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_reference.hpp>

#include <boost/static_assert.hpp>

#include <boost/utility/addressof.hpp>


namespace visitor { namespace rtti {

    namespace impl {
	
        template <class target>
        struct cast_visitor
        {
            typedef target to;
            to* result;

            cast_visitor() 
                : result(0)
            {}
			
			void impl(void const*) 
			{
				// no better match, casting failed
			}
			
			void impl(target* from) {
				// pointers to source can be interpreted as pointers to target 
				result=from;
			}
			
			template<class source>
			void operator()(source& from) {
				this->impl(boost::addressof(from));			
			}

        };

	} // NS impl
	
	template<class to,class from>
	to cast(from* source)
	{
		typedef typename boost::is_pointer<to>::type to_pointer;
		BOOST_STATIC_ASSERT(to_pointer::value);
	
		typedef typename boost::remove_pointer<to>::type to_wo_pointer;
		typedef typename boost::is_const<to_wo_pointer>::type to_const;
		typedef typename boost::is_const<from>::type from_const;
		BOOST_STATIC_ASSERT((to_const::value >= from_const::value));
	
		if (source==0)
			return 0;
		impl::cast_visitor<typename boost::remove_pointer<to>::type> v;
		accept(*source,v);
		return v.result;
	}

	template<class to,class from>
	to cast(from& source)
	{
		typedef typename boost::is_reference<to>::type to_reference;
		BOOST_STATIC_ASSERT(to_reference::value);

		typedef typename boost::is_const<to>::type to_const;
		typedef typename boost::is_const<from>::type from_const;
		BOOST_STATIC_ASSERT((to_const::value >= from_const::value));

		impl::cast_visitor<typename boost::remove_reference<to>::type> v;
		accept(source, v);
		if (!v.result)
			throw std::bad_cast();
		return *(v.result);
	}

}} // NS visitor::rtti

#endif