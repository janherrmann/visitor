#ifndef VISITOR_ACCEPT_BOOL_HPP
#define VISITOR_ACCEPT_BOOL_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace visitor {

    template<class Source,class StaticVisitor,class CastingPolicy>
    void accept_bool(bool b,Source& s, StaticVisitor& sv, CastingPolicy cp)
    {
        if (b)
            sv(cp.template cast<true>(s));
        else
            sv(cp.template cast<false>(s));
    }


} // NS visitor

#endif