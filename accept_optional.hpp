#ifndef VISITOR_ACCEPT_OPTIONAL_HPP
#define VISITOR_ACCEPT_OPTIONAL_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/optional.hpp>

#include "no_value.hpp"
#include "accept_bool.hpp"

namespace visitor {

    struct empty_optional_tag;
    typedef no_value<empty_optional_tag> empty_optional;

    namespace impl {
        template<bool b,class T>
        struct optional_casting_policy_helper
        {
            typedef T& result;
            static result cast_(boost::optional<T>& o) { return o.get(); }

        };
        template<bool b,class T>
        struct optional_casting_policy_helper<b,T const>
        {
            typedef T const& result;
            static result cast_(boost::optional<T> const& o) { return o.get(); }

        };

        template<class T>
        struct optional_casting_policy_helper<false,T const>
        {
            typedef empty_optional result;
            static result cast_(boost::optional<T> const&) { return result(); }
        };

        template<class T>
        struct optional_casting_policy_helper<false,T>
            : optional_casting_policy_helper<false,T const>
        {};
    } // NS impl

    struct optional_casting_policy {
        template <bool b,class T> 
        typename impl::optional_casting_policy_helper<b,T>::result cast(boost::optional<T>& optional)
        {
            return impl::optional_casting_policy_helper<b,T>::cast_(optional);
        }

        template <bool b,class T> 
        typename impl::optional_casting_policy_helper<b,T const>::result cast(boost::optional<T> const& optional)
        {
            return impl::optional_casting_policy_helper<b,T const>::cast_(optional);
        }
    };

    template<class T,class static_visitor>
    void accept(boost::optional<T>& optional,static_visitor& sv)
    {
        accept_bool(static_cast<bool>(optional), optional, sv, optional_casting_policy());
    };
    
    template<class T,class static_visitor>
    void accept(boost::optional<T> const& optional,static_visitor& sv)
    {
        accept_bool(static_cast<bool>(optional), optional, sv, optional_casting_policy());
    };
} // NS visitor

#endif
