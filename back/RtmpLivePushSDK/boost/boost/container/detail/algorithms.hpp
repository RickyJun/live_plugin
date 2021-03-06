//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ALGORITHMS_HPP
#define BOOST_CONTAINER_DETAIL_ALGORITHMS_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include "config_begin.hpp"
#include "workaround.hpp"

#include "has_trivial_copy.hpp"
#include "has_trivial_assign.hpp"
#include "no_exceptions_support.hpp"

#include "type_traits.hpp"
#include "mpl.hpp"
#include "iterators.hpp"


#include <cstring>

namespace boost {
namespace container {

template<class A, class T, class InpIt>
inline void construct_in_place(A &a, T* dest, InpIt source)
{     boost::container::allocator_traits<A>::construct(a, dest, *source);  }
//#endif

template<class A, class T, class U, class D>
inline void construct_in_place(A &a, T *dest, default_construct_iterator<U, D>)
{
   boost::container::allocator_traits<A>::construct(a, dest);
}

template<class A, class T, class U, class EF, class D>
inline void construct_in_place(A &a, T *dest, emplace_iterator<U, EF, D> ei)
{
   ei.construct_in_place(a, dest);
}

}  //namespace container {
}  //namespace boost {

#include "config_end.hpp"

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ALGORITHMS_HPP

