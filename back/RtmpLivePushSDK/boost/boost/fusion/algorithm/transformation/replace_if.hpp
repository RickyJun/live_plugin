/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0939)
#define FUSION_REPLACE_IF_08182005_0939

#include "transform_view.hpp"
#include "replace_if.hpp"
#include "is_sequence.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F, typename T>
        struct replace_if
        {
            typedef transform_view<Sequence, detail::replacer_if<F, T> > type;
        };
    }

    template <typename Sequence, typename F, typename T>
    inline 
    typename 
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace_if<Sequence const, F, T>::type
        >::type
    replace_if(Sequence const& seq, F pred, T const& new_value)
    {
        typedef typename result_of::replace_if<Sequence const, F, T>::type result;
        detail::replacer_if<F, T> f(pred, new_value);
        return result(seq, f);
    }
}}

#endif

