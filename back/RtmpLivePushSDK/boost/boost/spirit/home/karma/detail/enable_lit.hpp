//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DETAIL_ENABLE_LIT_JAN_06_2011_1009PM)
#define BOOST_SPIRIT_KARMA_DETAIL_ENABLE_LIT_JAN_06_2011_1009PM

#if defined(_MSC_VER)
#pragma once
#endif

#include "domain.hpp"
#include "generator.hpp"
#include "meta_compiler.hpp"
#include "lazy.hpp"
#include "vector.hpp"
#include "string_traits.hpp"
#include "common_terminals.hpp"

namespace boost { namespace spirit
{
    // enables lazy lit(...) for karma
    template <>
    struct use_lazy_terminal<karma::domain, tag::lit, 1> 
      : mpl::true_ {};
}}

#endif

