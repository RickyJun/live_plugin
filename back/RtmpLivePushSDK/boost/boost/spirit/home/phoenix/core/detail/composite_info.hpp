/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_CORE_DETAIL_COMPOSITE_INFO_HPP
#define PHOENIX_CORE_DETAIL_COMPOSITE_INFO_HPP

#include "if.hpp"
#include "greater.hpp"
#include "int.hpp"
#include "fold.hpp"

namespace boost { namespace phoenix { namespace detail
{
    struct max_nesting
    {
        template <typename T, typename State>
        struct result :
            mpl::if_<
                mpl::greater<typename T::nesting, State>
              , typename T::nesting
              , State
            >
        {};
    };

    template <typename ActorTuple>
    struct compute_nesting
    {
        typedef typename
            fusion::meta::fold<ActorTuple, mpl::int_<0>, max_nesting>::type
        type;
    };

}}}

#endif

