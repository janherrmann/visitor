#if !BOOST_PP_IS_ITERATING

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#   ifndef VISITOR_ACCEPT_UNSIGNED_INT_HPP
#   define VISITOR_ACCEPT_UNSIGNED_INT_HPP

#	include <boost/preprocessor/iteration/local.hpp>
#   include <boost/preprocessor/iteration/iterate.hpp>
#   include <boost/preprocessor/repetition/enum.hpp>
#   include <boost/preprocessor/arithmetic/dec.hpp>

#   include "config.hpp"

namespace visitor {

    namespace impl {
        template<unsigned int i> struct accept_unsigned_int_impl;

        template<>
        struct accept_unsigned_int_impl<0>
        {
            template<class Source,class StaticVisitor,class CastingPolicy>
            void operator()(unsigned int, Source&, StaticVisitor&, CastingPolicy)
            {};
        };

    } // NS impl


    template<unsigned int max,class Source,class StaticVisitor,class CastingPolicy>
    void accept_unsigned_int(unsigned int i,Source& s, StaticVisitor& sv, CastingPolicy cp)
    {
        impl::accept_unsigned_int_impl<max> accept_implementation;
        accept_implementation(i, s, sv, cp);
    }

#       define BOOST_PP_ITERATION_PARAMS_1 (3, (1, VISITOR_MAX_VISITABLE_CLASSES, "accept_unsigned_int.hpp"))
#       include BOOST_PP_ITERATE()
    
} // NS JHlib

#   endif //JH_LIB_ACCEPT_UNSIGNED_INT_HPP

#else // BOOST_PP_IS_ITERATING

#   define N BOOST_PP_ITERATION()

    namespace impl {

        template<>
        struct accept_unsigned_int_impl<N>
        {
            template<class Source,class StaticVisitor,class CastingPolicy>
            void operator()(unsigned int i, Source& s, StaticVisitor& sv, CastingPolicy cp)
            {
                switch (i) {

#   define BOOST_PP_LOCAL_LIMITS (0,BOOST_PP_DEC(N))
#   define BOOST_PP_LOCAL_MACRO(n)                                                  \
                case n : sv(cp.template cast<n>(s)); break;
#   include BOOST_PP_LOCAL_ITERATE()

                }
            }
        };

    } // NS impl

#endif // BOOST_PP_IS_ITERATING
