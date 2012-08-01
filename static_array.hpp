/* The following code declares class static_array,
 * an STL container (as wrapper) for arrays staticaly initialized of constant size with constant elements.
 * 
 * the basic (container) implementation is copied from Boost.Array

 
 * (C) Copyright Jan Herrmann 2012
 * (C) Copyright Nicolai M. Josuttis 2001.
 
 * The original author site is at: http://www.josuttis.com/
 
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
  * 05 Jul 2012 - copied the file and adapted to my needs (Jan Herrmann)
 * 28 Dec 2010 - (mtc) Added cbegin and cend (and crbegin and crend) for C++Ox compatibility.
 * 10 Mar 2010 - (mtc) fill method added, matching resolution of the standard library working group.
 *      See <http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#776> or Trac issue #3168
 *      Eventually, we should remove "assign" which is now a synonym for "fill" (Marshall Clow)
 * 10 Mar 2010 - added workaround for SUNCC and !STLPort [trac #3893] (Marshall Clow)
 * 29 Jan 2004 - c_array() added, BOOST_NO_PRIVATE_IN_AGGREGATE removed (Nico Josuttis)
 * 23 Aug 2002 - fix for Non-MSVC compilers combined with MSVC libraries.
 * 05 Aug 2001 - minor update (Nico Josuttis)
 * 20 Jan 2001 - STLport fix (Beman Dawes)
 * 29 Sep 2000 - Initial Revision (Nico Josuttis)
 *
 * Jan 29, 2004
 */
#ifndef VISITOR_STATIC_ARRAY_HPP
#define VISITOR_STATIC_ARRAY_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#   pragma warning(push)  
#   pragma warning(disable:4996) // 'std::equal': Function call with parameters that may be unsafe
#   pragma warning(disable:4510) // boost::array<T,N>' : default constructor could not be generated 
#   pragma warning(disable:4610) // warning C4610: class 'boost::array<T,N>' can never be instantiated - user defined constructor required 
#endif

#include <cstddef>
#include <stdexcept>
#include <boost/assert.hpp>

// Handles broken standard libraries better than <iterator>
#include <boost/detail/iterator.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>

// FIXES for broken compilers
#include <boost/config.hpp>


namespace visitor {

    template<class T>
    struct static_array {

        // type definitions
        typedef T               value_type;
        typedef T*              iterator;
        typedef const T*        const_iterator;
        typedef T&              reference;
        typedef const T&        const_reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;

        const_iterator const    elements_;          // pointer to first element
        size_type const         size_;              // container size

        // iterator support
        const_iterator  begin() const { return elements_; }
        const_iterator cbegin() const { return begin(); }
        
        const_iterator  end() const { return elements_+size_; }
        const_iterator cend() const { return end(); }

        // reverse iterator support
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC_STD_ITERATOR) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#elif defined(_MSC_VER) && (_MSC_VER == 1300) && defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB == 310)
        // workaround for broken reverse_iterator in VC7
        typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, iterator,
                                      reference, iterator, reference> > reverse_iterator;
        typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, const_iterator,
                                      const_reference, iterator, reference> > const_reverse_iterator;
#elif defined(_RWSTD_NO_CLASS_PARTIAL_SPEC) 
        typedef std::reverse_iterator<iterator, std::random_access_iterator_tag, 
              value_type, reference, iterator, difference_type> reverse_iterator; 
        typedef std::reverse_iterator<const_iterator, std::random_access_iterator_tag,
              value_type, const_reference, const_iterator, difference_type> const_reverse_iterator;
#else
        // workaround for broken reverse_iterator implementations
        typedef std::reverse_iterator<iterator,T> reverse_iterator;
        typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const {
            return rbegin();
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crend() const {
            return rend();
        }

        // operator[]
        const_reference operator[](size_type i) const 
        {     
            BOOST_ASSERT( i < size_ && "out of range" ); 
            return elements_[i]; 
        }

        // at() with range check
        const_reference at(size_type i) const { rangecheck(i); return elements_[i]; }
    
        // front() and back()
        const_reference front() const 
        {
            return elements_[0];
        }
        
        const_reference back() const
        { 
            return elements_[size_-1]; 
        }
        
        // size is constant
        size_type size() const { return size_; }
        bool empty() const { return size_!=0; }
        size_type max_size() const { return size_; }

        // direct access to data (read-only)
        const_iterator data() const { return elements_; }

        void rangecheck (size_type i) const {
            if (i >= size()) {
                std::out_of_range e("static_array<>: index out of range");
                boost::throw_exception(e);
            }
        }

    };

    // comparisons
    template<class T>
    bool operator==(static_array<T> const& lhs, static_array<T> const& rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template<class T>
    bool operator<(static_array<T> const& lhs, static_array<T> const& rhs) {
        return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
    }
    template<class T>
    bool operator!=(static_array<T> const& lhs, static_array<T> const& rhs) {
        return !(lhs==rhs);
    }

    template<class T>
    bool operator>(static_array<T> const& lhs, static_array<T> const& rhs) {
        return (rhs<lhs);
    }

    template<class T>
    bool operator>=(static_array<T> const& lhs, static_array<T> const& rhs) {
        return !(lhs<rhs);
    }
    template<class T>
    bool operator<=(static_array<T> const& lhs, static_array<T> const& rhs) {
        return !(lhs>rhs);
    }


} // NS visitor


#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#   pragma warning(pop)  
#endif 

#endif 
