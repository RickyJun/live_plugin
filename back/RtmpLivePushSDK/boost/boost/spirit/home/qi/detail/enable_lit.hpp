//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_QI_DETAIL_ENABLE_LIT_JAN_06_2011_0945PM)
#define BOOST_SPIRIT_QI_DETAIL_ENABLE_LIT_JAN_06_2011_0945PM

#if defined(_MSC_VER)
#pragma once
#endif

#include "domain.hpp"
#include "parser.hpp"
#include "meta_compiler.hpp"
#include "lazy.hpp"
#include "vector.hpp"
#include "string_traits.hpp"
#include "common_terminals.hpp"

namespace boost { namespace spirit
{
    // enables lazy lit(...) for qi
    template <>
    struct use_lazy_terminal<qi::domain, tag::lit, 1> 
      : mpl::true_ {};
}}

#endif

