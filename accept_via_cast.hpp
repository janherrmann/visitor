#ifndef VISITOR_ACCEPT_VIA_CAST_HPP
#define VISITOR_ACCEPT_VIS_CAST_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// struct via_cast_visitable_wrapper implements an accept function wich 
// tries to cast given object to different types via a casting policy
// the implementation is simular to the StaticDispatcher from loki
// (see Andrei Alexandrescu: "Modern C++ Design" page 268)
// for requirements of casting_policy see:
// 	accept_any.hpp
// 	accept_polymorphic.hpp

#include <iostream>

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

namespace visitor {

    namespace impl {
	
		template<class T,class base>
		struct via_cast_visitable
			: base
		{
			via_cast_visitable(typename base::base_type& obj, typename base::casting_policy cp)
				: base(obj,cp)
			{} 
			
			template<class static_visitor>
			void accept(static_visitor& sv)
			{
				if (T* value=this->template cast<T>(this->object)) 
					sv(*value);
				else
					this->base::accept(sv);
			}
			
			template<class static_visitor>
			void accept(static_visitor& sv) const
			{
				if (T const* value=this->template cast<T>(this->object)) 
					sv(*value);
				else
					this->base::accept(sv);
			}
			
		}; // via_cast_visitable
		
		template<class s,class r>
		struct via_cast_visitable_helper
			: boost::mpl::fold
				<s,r,via_cast_visitable<boost::mpl::_2,boost::mpl::_1> >				
		{};
	} // NS impl	
	
	template<class base,class casting_policy_>
	struct via_cast_visitable_root
		: casting_policy_
	{
		typedef base base_type;
		typedef casting_policy_ casting_policy;
			
		base_type& object;
			
		via_cast_visitable_root(base_type& obj, casting_policy cp)
			: casting_policy(cp)
			, object(obj)
		{}
			
		template<class static_visitor>
		void accept(static_visitor&) const
		{}
	}; // via_cast_visitable_root
		
	
	template<class sequence,class root>
	struct via_cast_visitable_wrapper
		: impl::via_cast_visitable_helper<sequence,root>::type
	{
		typedef typename impl::via_cast_visitable_helper<sequence,root>::type base;
		via_cast_visitable_wrapper(typename base::base_type& obj, typename base::casting_policy cp)
			: base(obj, cp)
		{}
		
		using base::accept;			
	}; // via_cast_visitable_wrapper
		
	template<class s,class r,class static_visitor>
	void accept(via_cast_visitable_wrapper<s,r>& obj, static_visitor& sv)
	{
		obj.accept(sv);
	}
		
	template<class s,class r,class static_visitor>
	void accept(via_cast_visitable_wrapper<s,r> const& obj, static_visitor& sv)
	{
		obj.accept(sv);
	}

} //  NS visitor

#endif
