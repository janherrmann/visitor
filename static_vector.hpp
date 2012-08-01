#if !BOOST_PP_IS_ITERATING
#   ifndef STATICVECTOR_HPP
#       define STATICVECTOR_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/repetition/enum.hpp>

#       include <boost/mpl/size.hpp>
#       include <boost/mpl/at.hpp>

#       include "static_array.hpp"

namespace visitor {
    namespace impl {
        template <class ElementType,class Sequence,std::size_t size>
        struct array_impl;

        template<class E,class S>
        struct array_impl<E,S,0>
        {
            typedef array_impl type;

            enum { size=0 };

            typedef E const * const value_type;
            static value_type value;
        };

        template<class E,class S>
        typename array_impl<E,S,0>::value_type array_impl<E,S,0>::value = 0;

#       define M0(z,n,data) boost::mpl::at_c<data,n>::type::value

#       define BOOST_PP_ITERATION_LIMITS (1, 10)
#       define BOOST_PP_FILENAME_1 "static_vector.hpp"
#       include BOOST_PP_ITERATE()

#       undef M0

    } // NS impl


    template<class ElementType,class Sequence>
    struct static_vector
    {
        struct holder {
            typedef impl::array_impl<ElementType,Sequence,boost::mpl::size<Sequence>::type::value> value_type;
            static value_type value;
        };

        typedef static_array<ElementType> value_type;
        static value_type value;
    };
    template<class E,class S>
    typename static_vector<E,S>::value_type static_vector<E,S>::value = 
    {
        static_vector<E,S>::holder::value.value,
        static_vector<E,S>::holder::value.size
    };

} // NS visitor


#   endif
#else // BOOST_PP_IS_ITERATING

#   define N BOOST_PP_ITERATION()

        template<class E,class S>
        struct array_impl<E,S,N>
        {
            typedef array_impl type;

            enum { size=N };

            typedef E const value_type[N];
            static value_type value;
        };

        template<class E,class S>
        typename array_impl<E,S,N>::value_type array_impl<E,S,N>::value = {
            BOOST_PP_ENUM(N, M0, S) 
        };


#endif // !BOOST_PP_IS_ITERATING
