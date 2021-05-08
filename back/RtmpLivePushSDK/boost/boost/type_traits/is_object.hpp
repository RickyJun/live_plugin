
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_IS_OBJECT_HPP_INCLUDED
#define BOOST_TT_IS_OBJECT_HPP_INCLUDED

#include "is_reference.hpp"
#include "is_void.hpp"
#include "is_function.hpp"
#include "ice_and.hpp"
#include "ice_not.hpp"
#include "config.hpp"

// should be the last #include
#include "bool_trait_def.hpp"

namespace boost {

namespace detail {

template <typename T>
struct is_object_impl
{
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_void<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_function<T>::value>::value
      >::value));
#else
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_void<T>::value>::value
      >::value));
#endif
};

} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF1(is_object,T,::boost::detail::is_object_impl<T>::value)

} // namespace boost

#include "bool_trait_undef.hpp"

#endif // BOOST_TT_IS_OBJECT_HPP_INCLUDED
