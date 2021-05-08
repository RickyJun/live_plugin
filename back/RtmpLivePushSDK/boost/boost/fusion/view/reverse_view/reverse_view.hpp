/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_07202005_0836)
#define FUSION_REVERSE_VIEW_07202005_0836

#include "access.hpp"
#include "is_view.hpp"
#include "category_of.hpp"
#include "reverse_view_iterator.hpp"
#include "begin_impl.hpp"
#include "end_impl.hpp"
#include "at_impl.hpp"
#include "value_at_impl.hpp"
#include "sequence_base.hpp"
#include "begin.hpp"
#include "end.hpp"
#include "size.hpp"
#include "is_base_of.hpp"
#include "static_assert.hpp"
#include "bool.hpp"
#include "eval_if.hpp"
#include "inherit.hpp"
#include "identity.hpp"

namespace boost { namespace fusion
{
    struct reverse_view_tag;
    struct fusion_sequence_tag;

    template <typename Sequence>
    struct reverse_view : sequence_base<reverse_view<Sequence> >
    {
        typedef reverse_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef Sequence seq_type;
        typedef typename traits::category_of<Sequence>::type category;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef typename result_of::size<Sequence>::type size;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , typename traits::category_of<first_type>::type>::value));

        reverse_view(Sequence& in_seq)
            : seq(in_seq)
        {}

        first_type first() const { return fusion::begin(seq); }
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;

    private:
        // silence MSVC warning C4512: assignment operator could not be generated
        reverse_view& operator= (reverse_view const&);
    };
}}

#endif


