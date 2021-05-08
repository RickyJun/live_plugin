/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_23_2009_0948PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_23_2009_0948PM

#include "iterator_base.hpp"
#include "category_of.hpp"
#include "begin.hpp"
#include "end.hpp"
#include "mpl_iterator.hpp"

#include "size_impl.hpp"
#include "begin_impl.hpp"
#include "end_impl.hpp"
#include "deref_impl.hpp"
#include "value_of_impl.hpp"
#include "next_impl.hpp"
#include "prior_impl.hpp"
#include "at_impl.hpp"
#include "value_at_impl.hpp"
#include "advance_impl.hpp"
#include "distance_impl.hpp"
#include "equal_to_impl.hpp"

namespace boost { namespace fusion
{
    struct nview_iterator_tag;
    struct random_access_traversal_tag;

    template<typename Sequence, typename Pos>
    struct nview_iterator
      : iterator_base<nview_iterator<Sequence, Pos> >
    {
        typedef nview_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;

        typedef Sequence sequence_type;
        typedef mpl_iterator<Pos> first_type;

        explicit nview_iterator(Sequence& in_seq)
          : seq(in_seq) {}

        Sequence& seq;

    private:
        // silence MSVC warning C4512: assignment operator could not be generated
        nview_iterator& operator= (nview_iterator const&);
    };

}}

#endif


