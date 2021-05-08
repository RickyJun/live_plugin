/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2009 Francois Barel

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_EXTRACT_PARAM_AUGUST_08_2009_0848AM)
#define BOOST_SPIRIT_EXTRACT_PARAM_AUGUST_08_2009_0848AM

#if defined(_MSC_VER)
#pragma once
#endif

#include "meta_compiler.hpp"
#include "locals.hpp"
#include "unused.hpp"
#include "common_terminals.hpp"

#include "is_function.hpp"
#include "parameter_types.hpp"
#include "result_type.hpp"
#include "as_list.hpp"
#include "as_vector.hpp"
#include "deref.hpp"
#include "end.hpp"
#include "eval_if.hpp"
#include "find_if.hpp"
#include "identity.hpp"
#include "if.hpp"
#include "placeholders.hpp"
#include "is_same.hpp"

namespace boost { namespace spirit { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // Helpers to extract params (locals, attributes, ...) from nonterminal
    // template arguments
    ///////////////////////////////////////////////////////////////////////////
    template <typename Types, typename Pred, typename Default>
    struct extract_param
    {
        typedef typename mpl::find_if<Types, Pred>::type pos;

        typedef typename
            mpl::eval_if<
                is_same<pos, typename mpl::end<Types>::type>
              , mpl::identity<Default>
              , mpl::deref<pos>
            >::type
        type;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Types>
    struct extract_locals
      : fusion::result_of::as_vector<
            typename extract_param<
                Types
              , is_locals<mpl::_>
              , locals<>
            >::type
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Domain, typename Types>
    struct extract_component
      : spirit::result_of::compile<
            Domain
          , typename extract_param<
                Types
              , traits::matches<Domain, mpl::_>
              , unused_type
            >::type
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Types>
    struct extract_sig
      : extract_param<
            Types
          , function_types::is_function<mpl::_>
          , void()
        >
    {};

    template <typename Sig>
    struct attr_from_sig
    {
        typedef typename function_types::result_type<Sig>::type attr;

        typedef typename
            mpl::if_<
                is_same<attr, void>
              , unused_type
              , attr
            >::type
        type;
    };

    template <typename Sig>
    struct params_from_sig
    {
        typedef typename function_types::parameter_types<Sig>::type params;

        typedef typename fusion::result_of::as_list<params>::type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Types>
    struct extract_encoding
      : extract_param<
            Types
          , is_char_encoding<mpl::_>
          , unused_type
        >
    {};
}}}

#endif
