#ifndef VISITOR_SELFMADECLASS_HPP
#define VISITOR_SELFMADECLASS_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>

#include "type.hpp"
#include "type_holder.hpp"
#include "accept_unsigned_int.hpp"


namespace visitor {

	struct destroy_visitor {
		std::size_t result;
		
		template<class T>
		void operator()(T const& obj) 
		{
			obj.T::~T(obj);
			result=sizeof(T);
		}		
	};
	
	template<class crtp_,class visitable_types_>
	class selfmadeclass
	{
	public:
		typedef crtp_ 				base_visitable;
		typedef visitable_types_ 	visitable_types;
	
		typedef std::size_t 		type_identifier;
		
		typedef type_holder<visitable_types,type_identifier> typeholder;
		
		type_identifier get_id() const
		{
			return this->id;
		}
		
		std::size_t destroy() const {			
			destroy_visitor v;
			accept(*this, v);
			return v.result;
		}
		
		struct casting_policy {
			template<unsigned int t_id>
			struct get_type
				: boost::mpl::at_c<visitable_types,t_id>
			{};
			
		
			template <unsigned int t_id>
			typename get_type<t_id>::type const& cast(selfmadeclass const& obj) {
				return static_cast<typename get_type<t_id>::type const&>(obj);
			}
			
			template <unsigned int t_id>
			typename get_type<t_id>::type& cast(selfmadeclass& obj) {
				return static_cast<typename get_type<t_id>::type&>(obj);
			}
		
		};
		
	protected:
		selfmadeclass(typeholder type)
			: id(type.id)
		{}
		
		~selfmadeclass() {}
		
	private:
		type_identifier const id;
	};
	

	
	template<class c,class v,class static_visitor>
	void accept(selfmadeclass<c,v> const& obj, static_visitor& sv) {
		typedef selfmadeclass<c,v> class_;
		accept_unsigned_int<boost::mpl::size<typename class_::visitable_types>::type::value>
			(obj.get_id(), obj, sv, typename class_::casting_policy());
	}
	
	template<class c,class v,class static_visitor>
	void accept(selfmadeclass<c,v>& obj, static_visitor& sv) {
		typedef selfmadeclass<c,v> class_;
		accept_unsigned_int<boost::mpl::size<typename class_::visitable_types>::type::value>
			(obj.get_id(), obj, sv, typename class_::casting_policy());
	}
	
};

#endif
