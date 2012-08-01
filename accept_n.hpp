#ifndef VISITOR_ACCEPT_N_HPP
#define VISITOR_ACCEPT_N_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace visitor {

    namespace impl {

        template<class Arg0,class StaticVisitor>
        struct accept2_sv_2
        {
            Arg0& arg0_;
            StaticVisitor& sv_;
            accept2_sv_2(Arg0& arg0, StaticVisitor& sv)
                : arg0_(arg0)
                , sv_(sv)
            {}

            template<class Arg1>
            void operator()(Arg1& arg1_)
            {
                sv_(arg0_,arg1_);
            }
        };

        template<class Arg1,class StaticVisitor>
        struct accept2_sv_1
        {
            Arg1& arg1_;
            StaticVisitor& sv_;
            accept2_sv_1(Arg1& arg1,StaticVisitor& sv)
                : arg1_(arg1)
                , sv_(sv)
            {}

            template<class Arg0>
            void operator()(Arg0& arg0_) 
            {
                accept2_sv_2<Arg0,StaticVisitor> sv(arg0_,sv_);
                accept(arg1_,sv);
            }
        };

    } // NS impl

    template<class Arg0,class StaticVisitor>
    void accept_1(Arg0& arg0, StaticVisitor& sv) 
    {
        accept(arg0,sv);
    }

    template<class Arg0,class Arg1,class StaticVisitor>
    void accept_2(Arg0& arg0, Arg1& arg1, StaticVisitor& sv) {
        visitor::impl::accept2_sv_1<Arg1,StaticVisitor> local_static_visitor(arg1,sv);
        accept(arg0,local_static_visitor);    
    }

} //  NS visitor

#endif
