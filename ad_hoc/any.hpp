#ifndef VISITOR_AFD_HOC_ANY_HPP
#define VISITOR_AFD_HOC_ANY_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/any.hpp>

#include "base.hpp"


namespace visitor { namespace ad_hoc { namespace any {

	struct any_casting_policy
	{
		template<class T>
		T* cast(boost::any& any) const {
			return boost::any_cast<T>(&any);
		}
		
		template<class T>
		T const* cast(boost::any const& any) const {
			return boost::any_cast<T>(&any);
		}
	};
	
	template<class sequence>
	visitable_wrapper<
		sequence,
		base_visitable_root<
			boost::any,
			any_casting_policy
		> 
	> wrap(boost::any& any)
	{
		visitable_wrapper<
			sequence,
			base_visitable_root<
				boost::any,
				any_casting_policy
			> 
		>	result(any, any_casting_policy());
		return result;
	}
	
	template<class sequence>
	visitable_wrapper<
		sequence,
		base_visitable_root<
			boost::any const,
			any_casting_policy
		> 
	> wrap(boost::any const& any)
	{
		visitable_wrapper<
			sequence,
			base_visitable_root<
				boost::any const,
				any_casting_policy
			> 
		>	result(any, any_casting_policy());
		return result;
	}
	
	template<class sequence>
	visitable_wrapper
		< sequence
		, base_visitable_root
			< boost::any const
			, any_casting_policy
			> 
		> c_wrap(boost::any const& any)
	{
		visitable_wrapper<
			sequence,
			base_visitable_root<
				boost::any const,
				any_casting_policy
			> 
		>	result(any, any_casting_policy());
		return result;
	}

}}} // NS visitor::ad_hoc::any

#endif
