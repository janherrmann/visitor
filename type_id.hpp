#ifndef VISITOR_TYPES_HPP
#define VISITOR_TYPES_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt

#include <exception>
#include <typeinfo>

#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include <boost/mpl/size.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>

#include <boost/utility/enable_if.hpp>

#include "type.hpp"

#include "visitable_classes.hpp"
#include "accept_unsigned_int.hpp"
#include "static_vector.hpp"


namespace visitor {

    struct type_error
        : std::exception
    {};


    template<class base_type>
    class type_id
        : boost::totally_ordered<type_id<base_type> >
    {
    public:
        typedef base_type base_visitable;
        typedef visitor::visitable_classes<base_visitable> visitable_classes;
        typedef std::size_t type_identifier;

        enum { empty = boost::mpl::size<visitable_classes>::type::value };

        type_id() 
            : type_id_(empty)
        {}

        explicit type_id(type_identifier t_id) 
            : type_id_(t_id)
        {
            if (t_id> empty) 
            {
                type_error ex;
                boost::throw_exception(ex);
            }
        }

        template<class T>
        struct TypePos
            : boost::mpl::find<visitable_classes,T>::type::pos
        {};

        template<class T>
        type_id(type<T>, typename boost::enable_if<boost::mpl::contains<visitable_classes,T> >::type* dummy=0)
            : type_id_(TypePos<T>::value)
        {}

        type_identifier get_type_id() const {
            return type_id_;
        }
        
        bool is_empty() const {
            return type_id_==empty;
        }

        struct type_casting_policy 
        {
            template <unsigned int n>
            type<typename boost::mpl::at_c<visitable_classes,n>::type> cast(type_id const&) 
            {
                return type<typename boost::mpl::at_c<visitable_classes,n>::type>();
            }
        };
    private:
        type_identifier type_id_;
    }; // class type_id


    template<class B>
    bool operator<(type_id<B> const& lhs,type_id<B> const& rhs) {
        return lhs.get_type_id() < rhs.get_type_id();
    }
    
    template<class B>
    bool operator==(type_id<B> const& lhs,type_id<B> const& rhs) {
        return lhs.get_type_id() == rhs.get_type_id();
    }
    
    template<class base_class,class static_visitor>
    void accept(type_id<base_class> const& obj, static_visitor& sv)
    {
        accept_unsigned_int<type_id<base_class>::empty>(
            obj.get_type_id(),
            obj,
            sv,
            typename type_id<base_class>::type_casting_policy()
        );
    }

    namespace impl {
        template<class b>
        struct identify_visitor
        {
            type_id<b> result;

            template <class T>
            void operator()(T const&) {
                result=type<T>(); 
            }
        };
    } // NS impl

    template<class base_class>
    type_id<base_class> identify(base_class const& obj)
    {
        impl::identify_visitor<base_class> sv;
        accept(obj,sv);
        return sv.result;        
    }

    namespace impl {
        struct type_info_visitor
        {
            std::type_info const* result;
            template<class T>
            void operator()(type<T>)
            {
                result=&typeid(T);
            };
            type_info_visitor() 
                : result(0)
            {}
        };

    } // NS impl

    template<class base_class>
    std::type_info const& type_info_(type_id<base_class> const& obj)
    {
        if (obj.is_empty())
            return typeid(void);
        impl::type_info_visitor sv;
        accept(obj,sv);
        return *sv.result;
    }

    namespace impl {
        template<class base_class>
        struct create_visitor {
            base_class* result;
            create_visitor()
                : result(0)
            {};

            template<class T>
            void operator()(type<T>)
            {
                result=new T;
            }
        };
    } // NS impl

    template<class base_class>
    base_class* create_(type_id<base_class> const& obj)
    {
        if (obj.is_empty())
            return 0;
        impl::create_visitor<base_class> sv;
        accept(obj, sv);
        return sv.result;
    }

    template<class result,class metafunctionclass,class base_class>
    result traits_helper(type_id<base_class> const& obj) {
        return static_vector<
            result,
            typename boost::mpl::transform_view<
                typename type_id<base_class>::visitable_classes,
                metafunctionclass
            >::type
        >::value.at(obj.get_type_id());
    }

    template<class base_class>

    std::size_t sizeof_(type_id<base_class> const& obj) {
        if (obj.is_empty()) 
            return 0;

        return traits_helper<std::size_t,boost::mpl::sizeof_<boost::mpl::_> >(obj);
    }

} // NS visitor

#endif
