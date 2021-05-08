/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_ITERATOR_07202005_0835)
#define FUSION_REVERSE_VIEW_ITERATOR_07202005_0835

#include "iterator_base.hpp"
#include "category_of.hpp"
#include "convert_iterator.hpp"
#include "mpl_iterator.hpp"
#include "deref_impl.hpp"
#include "next_impl.hpp"
#include "prior_impl.hpp"
#include "advance_impl.hpp"
#include "distance_impl.hpp"
#include "value_of_impl.hpp"
#include "deref_data_impl.hpp"
#include "value_of_data_impl.hpp"
#include "key_of_impl.hpp"
#include "is_base_of.hpp"
#include "static_assert.hpp"

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename First>
    struct reverse_view_iterator
        : iterator_base<reverse_view_iterator<First> >
    {
        typedef convert_iterator<First> converter;
        typedef typename converter::type first_type;
        typedef reverse_view_iterator_tag fusion_tag;
        typedef typename traits::category_of<first_type>::type category;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , category>::value));

        reverse_view_iterator(First const& in_first)
            : first(converter::call(in_first)) {}

        first_type first;

    private:
        // silence MSVC warning C4512: assignment operator could not be generated
        reverse_view_iterator& operator= (reverse_view_iterator const&);
    };
}}

#endif

