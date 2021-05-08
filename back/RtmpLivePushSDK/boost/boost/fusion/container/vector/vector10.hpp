/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR10_05042005_0257)
#define FUSION_VECTOR10_05042005_0257

#include "vector10_fwd.hpp"
#include "sequence_base.hpp"
#include "access.hpp"
#include "next.hpp"
#include "deref.hpp"
#include "begin.hpp"
#include "at_impl.hpp"
#include "value_at_impl.hpp"
#include "begin_impl.hpp"
#include "end_impl.hpp"

#include "void.hpp"
#include "int.hpp"
#include "bool.hpp"
#include "at.hpp"
#include "vector10.hpp"
#include "is_convertible.hpp"
#include "enable_if.hpp"

#include "dec.hpp"
#include "iterate.hpp"
#include "enum.hpp"
#include "enum_shifted.hpp"
#include "enum_params.hpp"
#include "enum_binary_params.hpp"
#include "repeat_from_to.hpp"

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

    template <typename Dummy>
    struct vector0 : sequence_base<vector0<Dummy> >
    {
        typedef mpl::vector0<> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<0> size;

        vector0() {}

        template<typename Sequence>
        vector0(Sequence const& /*seq*/)
        {}
    };
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include "vector10.hpp"
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/vector10.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{

// expand vector1 to vector10
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/vector_n.hpp"
#define BOOST_PP_ITERATION_LIMITS (1, 10)
#include BOOST_PP_ITERATE()

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
