#ifndef VISITOR_CAST_HPP
#define VISITOR_CAST_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>


namespace visitor {

    namespace impl {
        template <class target>
        struct cast_visitor
        {
            typedef target to;
            to* result;

            cast_visitor() 
                : result(0)
            {}

            template<class source>
            typename boost::enable_if<typename boost::is_base_of<target,source>::type>::type operator()(source& obj) 
            {
                result=&obj;
            }

            template<class source>
            typename boost::disable_if<typename boost::is_base_of<target,source>::type>::type operator()(source&) 
            {}
        };
    } // NS impl 


    template<class to,class from>
    to cast(from* source)
    {
        if (source==0)
            return 0;
        impl::cast_visitor<typename boost::remove_pointer<to>::type> v;
        accept(*source,v);

        return v.result;
    }

    template<class to,class from>
    to cast(from& source)
    {
        impl::cast_visitor<typename boost::remove_reference<to>::type> v;
        accept(source, v);
        if (!v.result)
            throw std::bad_cast();
        return *(v.result);
    }

} // NS visitor

#endif