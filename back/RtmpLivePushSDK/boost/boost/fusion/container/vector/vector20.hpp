/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR20_05052005_0205)
#define FUSION_VECTOR20_05052005_0205

#include "vector20_fwd.hpp"
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
#include "at.hpp"
#include "bool.hpp"
#include "vector20.hpp"
#include "is_convertible.hpp"
#include "enable_if.hpp"

#include "dec.hpp"
#include "iterate.hpp"
#include "enum.hpp"
#include "enum_shifted.hpp"
#include "enum_params.hpp"
#include "enum_binary_params.hpp"
#include "repeat_from_to.hpp"

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include "vector20.hpp"
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/vector20.hpp")
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
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

// expand vector11 to vector20
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/vector_n.hpp"
#define BOOST_PP_ITERATION_LIMITS (11, 20)
#include BOOST_PP_ITERATE()

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

