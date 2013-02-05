#ifndef VISITOR_AD_HOC_POLY_HPP
#define VISITOR_AD_HOC_POLY_HPP

// Copyright (c) 2012, 2013 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/*
    Implements an ah hoc visitable wrapper for 
	polymorphic types. 
	
*/
	
	

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/placeholders.hpp>

#include "base.hpp"

namespace visitor { namespace ad_hoc { namespace poly {

	struct polymorphic_casting_policy
	{
		template<class T,class S>
		T* cast(S& source) const {
			return dynamic_cast <T*>(&source);
		}
		
		template<class T,class S>
		T const* cast(S const& source) const {
			return dynamic_cast <T const*>(&source);
		}
	};
	
	namespace impl {
		template<class s>
		struct poly_sort
			: boost::mpl::sort
				< s
				, boost::is_base_of
					< boost::mpl::placeholders::_1
					, boost::mpl::placeholders::_2
					>
				>	
		{};
	}
	
	template<class sequence,class base>
	visitable_wrapper
		< typename impl::poly_sort<sequence>::type
		, base_visitable_root
			< base 
			, polymorphic_casting_policy
			> 
		> wrap(base& obj)
	{
		visitable_wrapper
			< typename impl::poly_sort<sequence>::type
			, base_visitable_root
				< base 
				, polymorphic_casting_policy
				> 
			> result(obj, polymorphic_casting_policy());
		return result;
	}
	
	template<class sequence,class base>
	visitable_wrapper
		< typename impl::poly_sort<sequence>::type
		, base_visitable_root
			< base const
			, polymorphic_casting_policy
			> 
		> wrap(base const& obj)
	{
		visitable_wrapper
			< typename impl::poly_sort<sequence>::type
			, base_visitable_root
				< base const
				, polymorphic_casting_policy
				> 
			> result(obj, polymorphic_casting_policy());
		return result;
	}
	
	template<class sequence,class base>
	visitable_wrapper
		< typename impl::poly_sort<sequence>::type
		, base_visitable_root
			< base const
			, polymorphic_casting_policy
			> 
		> c_wrap(base const& obj)
	{
		visitable_wrapper
			< typename impl::poly_sort<sequence>::type
			, base_visitable_root
				< base const
				, polymorphic_casting_policy
				> 
			> result(obj, polymorphic_casting_policy());
		return result;
	}


}}} //  NS visitor::ad_hoc::poly

#endif
