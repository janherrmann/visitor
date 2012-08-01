#if !BOOST_PP_IS_ITERATING

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#   ifndef VISITOR_GOFVISITOR_HPP
#       define VISITOR_GOFVISITOR_HPP


#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/iteration/local.hpp>
#       include <boost/preprocessor/cat.hpp>
#       include <boost/preprocessor/arithmetic/dec.hpp>

#       include <boost/mpl/size.hpp>
#       include <boost/mpl/at.hpp>

#       include "config.hpp"

namespace visitor {
    namespace impl {
        template<class crtp,class visitable_classes,unsigned int class_count>
        struct gofvisitor_impl;

        template<class c,class v>
        struct gofvisitor_impl<c,v,0>
        {
            typedef c base_visitor;
            typedef v visitable_classes;

            virtual ~gofvisitor_impl() {}

            template<class static_visitor,class casting_policy>
            struct concrete_visitor
                : base_visitor
                , casting_policy
            {
                static_visitor& sv_;
                concrete_visitor(static_visitor& sv, casting_policy cp)
                    : casting_policy(cp)
                    , sv_(sv)
                {}

            }; // concrete_visitor
        }; // gofvisitor_impl

#       define BOOST_PP_ITERATION_PARAMS_1 (3, (1, VISITOR_MAX_VISITABLE_CLASSES, "gofvisitor.hpp"))
#       include BOOST_PP_ITERATE()

    } // NS impl

    template<class crtp,class visitable_classes>
    struct gofvisitor
        : ::visitor::impl::gofvisitor_impl<crtp,visitable_classes,::boost::mpl::size<visitable_classes>::type::value>
    {};
    
    struct gofvisitor_nonconst_casting_policy
    {
        template<class T>
        T& cast(T const& obj) {
            return const_cast<T&>(obj);
        }
    };

    struct gofvisitor_const_casting_policy
    {
        template<class T>
        T const& cast(T const& obj) {
            return obj;
        }
    };
} // NS visitor

#   define VISITOR_GOFVISITOR_PURE_VIRTUAL_ACCEPT(VISITOR)                                                  \
    virtual void accept(VISITOR&) const = 0;
#   define VISITOR_GOFVISITOR_VIRTUAL_ACCEPT(VISITOR)                                                       \
    virtual void accept(VISITOR& v) const { v.visit(*this); }

#   define VISITOR_GOFVISITOR_NON_MEMBER_ACCEPT(BASE_CLASS,VISITOR)                                         \
    template<class static_visitor,class casting_policy>                                                     \
    void accept(BASE_CLASS const& obj, static_visitor& sv, casting_policy cp) {                             \
        VISITOR::concrete_visitor<static_visitor,casting_policy> v(sv,cp);                                  \
        obj.accept(v);                                                                                     \
    }                                                                                                       \
    template<class static_visitor>                                                                          \
    void accept(BASE_CLASS const& obj, static_visitor& sv) {                                                \
       accept(obj, sv, ::visitor::gofvisitor_const_casting_policy());                                       \
    }                                                                                                       \
    template<class static_visitor>                                                                          \
    void accept(BASE_CLASS& obj, static_visitor& sv) {                                                      \
       accept(obj, sv, ::visitor::gofvisitor_nonconst_casting_policy());                                    \
    }


#   endif // VISITOR_GOFVISITOR_HPP

#else //!BOOST_PP_IS_ITERATING

#   define N BOOST_PP_ITERATION()

        template<class c,class v>
        struct gofvisitor_impl<c,v,N>
        {
            typedef c base_visitor;
            typedef v visitable_classes;

            virtual ~gofvisitor_impl() {}

#   define BOOST_PP_LOCAL_MACRO(n)                                                                          \
            typedef typename boost::mpl::at_c<visitable_classes,n>::type BOOST_PP_CAT(visitable_type_,n);   \
            virtual void visit(BOOST_PP_CAT(visitable_type_,n) const&) = 0;
#   define BOOST_PP_LOCAL_LIMITS (0,BOOST_PP_DEC(N))
#   include BOOST_PP_LOCAL_ITERATE()

            template<class static_visitor,class casting_policy>
            struct concrete_visitor
                : base_visitor
                , casting_policy
            {
                static_visitor& sv_;
                concrete_visitor(static_visitor& sv, casting_policy cp)
                    : casting_policy(cp)
                    , sv_(sv)
                {}

#   define BOOST_PP_LOCAL_MACRO(n)                                                                          \
                virtual void visit(BOOST_PP_CAT(visitable_type_,n) const& obj) { sv_(this->cast(obj)); };
#   define BOOST_PP_LOCAL_LIMITS (0,BOOST_PP_DEC(N))
#   include BOOST_PP_LOCAL_ITERATE()

            }; // concrete_visitor
        }; // gofvisitor_impl

#endif // BOOST_PP_IS_ITERATING
