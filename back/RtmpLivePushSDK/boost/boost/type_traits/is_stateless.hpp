
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_IS_STATELESS_HPP_INCLUDED
#define BOOST_TT_IS_STATELESS_HPP_INCLUDED

#include "has_trivial_constructor.hpp"
#include "has_trivial_copy.hpp"
#include "has_trivial_destructor.hpp"
#include "is_class.hpp"
#include "is_empty.hpp"
#include "ice_and.hpp"
#include "config.hpp"

// should be the last #include
#include "bool_trait_def.hpp"

namespace boost {

namespace detail {

template <typename T>
struct is_stateless_impl
{
  BOOST_STATIC_CONSTANT(bool, value = 
    (::boost::type_traits::ice_and<
       ::boost::has_trivial_constructor<T>::value,
       ::boost::has_trivial_copy<T>::value,
       ::boost::has_trivial_destructor<T>::value,
       ::boost::is_class<T>::value,
       ::boost::is_empty<T>::value
     >::value));
};

} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF1(is_stateless,T,::boost::detail::is_stateless_impl<T>::value)

} // namespace boost

#include "bool_trait_undef.hpp"

#endif // BOOST_TT_IS_STATELESS_HPP_INCLUDED
