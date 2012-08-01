#ifndef VISITOR_ACCEPT_VARIANT_HPP
#define VISITOR_ACCEPT_VARIANT_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/variant.hpp>

namespace visitor {

    template<class StaticVisitor>
    struct VariantVisitor
        : boost::static_visitor<void>
    {
        StaticVisitor& sv_;
        VariantVisitor (StaticVisitor& sv) 
            : sv_(sv)
        {}

        template <class T>
        void operator()(T& t) const
        {
            sv_(t);
        };
    };


    template <BOOST_VARIANT_ENUM_PARAMS(class T),class StaticVisitor>
    void accept(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& v, StaticVisitor& sv)
    {
        boost::apply_visitor(VariantVisitor<StaticVisitor>(sv),v);
    };

    template <BOOST_VARIANT_ENUM_PARAMS(class T),class StaticVisitor>
    void accept(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& v, StaticVisitor& sv)
    {
        boost::apply_visitor(VariantVisitor<StaticVisitor>(sv),v);
    };

}

#endif