#ifndef VISITOR_NO_VALUE_HPP
#define VISITOR_NO_VALUE_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt

namespace visitor {

    // empty type indicating that original object 
    // is in an empty or unusable state 
    // (pointer==0, unset optional, unknown any, ...)
    template <class reason=void>
    struct no_value
    {};

    template<class reason,class static_visitor>
    void accept(no_value<reason> const&, static_visitor&)
    {}

} // NS visitor

#endif
