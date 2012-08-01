#ifndef VISITOR_CLONE_HPP
#define VISITOR_CLONE_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <iostream>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace visitor {

    namespace impl {
        template <class T>
        struct clone_visitor 
        {
            typedef T clone_type;
            std::auto_ptr<clone_type> result;

            template <class T2>
            typename boost::enable_if<typename boost::is_base_of<T,T2>::type>::type
                operator()(T2 const& obj)
            {
                result=std::auto_ptr<clone_type>(new T2(obj));
            }

            template <class T2>
            typename boost::disable_if<typename boost::is_base_of<T,T2>::type>::type
                operator()(T2 const& obj)
            {
                // the program should never arive this point
                // but the compiler needs an overload for other
                // posible visitable types 
            }

            clone_visitor()
                : result(0)
            {}
        }; // struct clone_visitor
    } // NS impl

    template<class T>
    std::auto_ptr<T> clone(T const& obj)
    {
        impl::clone_visitor<T> sv;
        accept(obj, sv);
        return sv.result;
    }

} // NS visitor

#endif
