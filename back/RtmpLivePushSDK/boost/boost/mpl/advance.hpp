
#ifndef BOOST_MPL_ADVANCE_HPP_INCLUDED
#define BOOST_MPL_ADVANCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: advance.hpp 49267 2008-10-11 06:19:02Z agurtovoy $
// $Date: 2008-10-10 23:19:02 -0700 (Fri, 10 Oct 2008) $
// $Revision: 49267 $

#include "advance_fwd.hpp"
#include "less.hpp"
#include "negate.hpp"
#include "long.hpp"
#include "if.hpp"
#include "tag.hpp"
#include "apply_wrap.hpp"
#include "advance_forward.hpp"
#include "advance_backward.hpp"
#include "value_wknd.hpp"
#include "na_spec.hpp"
#include "nttp_decl.hpp"

namespace boost { namespace mpl {

// default implementation for forward/bidirectional iterators
template< typename Tag >
struct advance_impl
{
    template< typename Iterator, typename N > struct apply
    {
        typedef typename less< N,long_<0> >::type backward_;
        typedef typename if_< backward_, negate<N>, N >::type offset_;

        typedef typename if_<
              backward_
            , aux::advance_backward< BOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            , aux::advance_forward< BOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            >::type f_;

        typedef typename apply_wrap1<f_,Iterator>::type type;
    };
};


template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    , typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct advance
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,N>
{
};

template<
      typename Iterator
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct advance_c
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,long_<N> >
{
};

BOOST_MPL_AUX_NA_SPEC(2, advance)

}}

#endif // BOOST_MPL_ADVANCE_HPP_INCLUDED
