// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include "config.hpp"

#include "member_with_tag.hpp"
#include "member_at.hpp"
#include "call_traits.hpp"
#include "is_const.hpp"
#include "if.hpp"
#include "not.hpp"
#include "enable_if.hpp"


/******************************************************************************
                   BIMAP SYMMETRIC ACCESS RESULT OF
*******************************************************************************

namespace result_of {

template< class Tag, class SymmetricType >
struct NAME
{
    typedef -unspecified- type;
};

} // namespace result_of

******************************************************************************/

/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER(                       \
                                                                              \
        NAME,                                                                 \
        METAFUNCTION_BASE                                                     \
    )                                                                         \
                                                                              \
    namespace result_of {                                                     \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    struct NAME                                                               \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME METAFUNCTION_BASE                      \
        <                                                                     \
            Tag,SymmetricType                                                 \
                                                                              \
        >::type value_type;                                                   \
                                                                              \
        typedef BOOST_DEDUCED_TYPENAME mpl::if_< is_const<SymmetricType>,     \
                                                                              \
            BOOST_DEDUCED_TYPENAME call_traits<value_type>::const_reference,  \
                                                                              \
            BOOST_DEDUCED_TYPENAME call_traits<value_type>::reference         \
                                                                              \
        >::type type;                                                         \
    };                                                                        \
                                                                              \
    }
/*===========================================================================*/



/******************************************************************************
                   BIMAP SYMMETRIC ACCESS IMPLEMENTATION
*******************************************************************************

namespace detail {

template< class Tag, class SymmetricType >
typename result_of::NAME<Tag,SymmetricType>::type
    NAME( Tag , const Relation & );

} // namespace detail

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER(                  \
                                                                              \
        NAME,                                                                 \
        TP_SYMMETRIC,                                                         \
        PARAMETER_NAME,                                                       \
        LEFT_BODY,                                                            \
        RIGHT_BODY                                                            \
    )                                                                         \
                                                                              \
    namespace detail {                                                        \
                                                                              \
                                                                              \
                                                                              \
    template< class TP_SYMMETRIC >                                            \
    BOOST_DEDUCED_TYPENAME result_of::NAME                                    \
    <                                                                         \
        ::boost::bimaps::relation::member_at::left,TP_SYMMETRIC               \
                                                                              \
    >::type                                                                   \
                                                                              \
    NAME( ::boost::bimaps::relation::member_at::left,                         \
                  TP_SYMMETRIC & PARAMETER_NAME )                             \
    {                                                                         \
        LEFT_BODY;                                                            \
    }                                                                         \
                                                                              \
    template< class TP_SYMMETRIC >                                            \
    BOOST_DEDUCED_TYPENAME result_of::NAME                                    \
    <                                                                         \
        ::boost::bimaps::relation::member_at::right,TP_SYMMETRIC              \
                                                                              \
    >::type                                                                   \
                                                                              \
    NAME( ::boost::bimaps::relation::member_at::right,                        \
                  TP_SYMMETRIC & PARAMETER_NAME )                             \
    {                                                                         \
        RIGHT_BODY;                                                           \
    }                                                                         \
                                                                              \
    }
/*===========================================================================*/


/******************************************************************************
                   BIMAP RELATION ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SymmetricType >
typename result_of::NAME<Tag,SymmetricType>::type
    NAME( const SymmetricType & );

******************************************************************************/

/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER(                       \
                                                                              \
        NAME                                                                  \
    )                                                                         \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    BOOST_DEDUCED_TYPENAME result_of::NAME<Tag,SymmetricType>::type           \
    NAME( SymmetricType & s )                                                 \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::   \
            member_with_tag                                                   \
            <                                                                 \
                Tag,SymmetricType                                             \
                                                                              \
            >::type member_at_tag;                                            \
                                                                              \
        return detail::NAME(member_at_tag(),s);                               \
    }
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP

