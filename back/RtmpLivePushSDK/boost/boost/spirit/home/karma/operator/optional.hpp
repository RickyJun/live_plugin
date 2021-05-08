//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SPIRIT_KARMA_OPTIONAL_MARCH_31_2007_0852AM)
#define SPIRIT_KARMA_OPTIONAL_MARCH_31_2007_0852AM

#if defined(_MSC_VER)
#pragma once
#endif

#include "domain.hpp"
#include "generator.hpp"
#include "meta_compiler.hpp"
#include "info.hpp"
#include "unused.hpp"
#include "attributes.hpp"
#include "container.hpp"
#include "has_semantic_action.hpp"
#include "handles_container.hpp"
#include "assert.hpp"
#include "optional.hpp"
#include "is_convertible.hpp"

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<karma::domain, proto::tag::negate> // enables -g
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct optional : unary_generator<optional<Subject> >
    {
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        // Build a boost::optional from the subject's attribute. Note
        // that boost::optional may return unused_type if the
        // subject's attribute is an unused_type.
        template <typename Context, typename Iterator = unused_type>
        struct attribute
          : traits::build_optional<
                typename traits::attribute_of<Subject, Context, Iterator>::type
            >
        {};

        optional(Subject const& subject)
          : subject(subject) {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx
          , Delimiter const& d, Attribute const& attr) const
        {
            if (traits::has_optional_value(attr)) 
                subject.generate(sink, ctx, d, traits::optional_value(attr));
            return sink_is_good(sink);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("optional", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::negate, Elements, Modifiers>
      : make_unary_composite<Elements, optional> {};

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::optional<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::optional<Subject>, Attribute, Context
          , Iterator>
      : mpl::true_ {};
}}}

#endif
