/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(SPIRIT_NO_SKIP_JAN_16_2010_0802PM)
#define SPIRIT_NO_SKIP_JAN_16_2010_0802PM

#if defined(_MSC_VER)
#pragma once
#endif

#include "meta_compiler.hpp"
#include "skip_over.hpp"
#include "parser.hpp"
#include "unused_skipper.hpp"
#include "unused.hpp"
#include "common_terminals.hpp"
#include "attributes.hpp"
#include "info.hpp"
#include "has_semantic_action.hpp"
#include "handles_container.hpp"

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<qi::domain, tag::no_skip> // enables no_skip
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::no_skip;
#endif
    using spirit::no_skip_type;

    // same as lexeme[], but does not pre-skip
    template <typename Subject>
    struct no_skip_directive : unary_parser<no_skip_directive<Subject> >
    {
        typedef Subject subject_type;
        no_skip_directive(Subject const& subject)
          : subject(subject) {}

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename
                traits::attribute_of<subject_type, Context, Iterator>::type
            type;
        };

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr) const
        {
            return subject.parse(first, last, context
              , detail::unused_skipper<Skipper>(skipper), attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("no_skip", subject.what(context));

        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::no_skip, Subject, Modifiers>
    {
        typedef no_skip_directive<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject, unused_type) const
        {
            return result_type(subject);
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<qi::no_skip_directive<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
        , typename Iterator>
    struct handles_container<qi::no_skip_directive<Subject>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif
