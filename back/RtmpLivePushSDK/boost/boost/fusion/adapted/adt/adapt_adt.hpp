/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP

#include "cat.hpp"
#include "empty.hpp"
#include "add_reference.hpp"
#include "is_const.hpp"
#include "add_const.hpp"
#include "remove_const.hpp"

#include "extension.hpp"
#include "adapt_base.hpp"
#include "at_impl.hpp"
#include "is_view_impl.hpp"
#include "is_sequence_impl.hpp"
#include "value_at_impl.hpp"
#include "category_of_impl.hpp"
#include "size_impl.hpp"
#include "begin_impl.hpp"
#include "end_impl.hpp"
#include "value_of_impl.hpp"
#include "deref_impl.hpp"
#include "extension.hpp"
#include "adapt_base.hpp"

#define BOOST_FUSION_ADAPT_ADT_FILLER_0(A, B, C, D)\
    ((A, B, C, D)) BOOST_FUSION_ADAPT_ADT_FILLER_1
#define BOOST_FUSION_ADAPT_ADT_FILLER_1(A, B, C, D)\
    ((A, B, C, D)) BOOST_FUSION_ADAPT_ADT_FILLER_0
#define BOOST_FUSION_ADAPT_ADT_FILLER_0_END
#define BOOST_FUSION_ADAPT_ADT_FILLER_1_END

#define BOOST_FUSION_ADAPT_ADT_C(TEMPLATE_PARAMS_SEQ, NAME_SEQ, I, ATTRIBUTE)   \
    BOOST_FUSION_ADAPT_ADT_C_BASE(                                              \
        TEMPLATE_PARAMS_SEQ, NAME_SEQ, I, ATTRIBUTE, 4)

#define BOOST_FUSION_ADAPT_TPL_ADT(TEMPLATE_PARAMS_SEQ, NAME_SEQ , ATTRIBUTES)  \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT(NAME, ATTRIBUTES)                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT_AS_VIEW(NAME, ATTRIBUTES)                        \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        1,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#endif
