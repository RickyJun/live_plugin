//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DIRECTIVE_FEB_21_2007_0833PM)
#define BOOST_SPIRIT_KARMA_DIRECTIVE_FEB_21_2007_0833PM

#if defined(_MSC_VER)
#pragma once
#endif

#include "encoding.hpp"

///////////////////////////////////////////////////////////////////////////////
//  directives related to alignment 
//  left_align[...], right_align[...], center[...]
///////////////////////////////////////////////////////////////////////////////
#include "left_alignment.hpp"
#include "right_alignment.hpp"
#include "center_alignment.hpp"

///////////////////////////////////////////////////////////////////////////////
//  directives related to truncating length
//  maxwidth[...], columns[]
///////////////////////////////////////////////////////////////////////////////
#include "maxwidth.hpp"
#include "columns.hpp"

///////////////////////////////////////////////////////////////////////////////
//  directives related to character case
//  lower[...] and upper[...]
///////////////////////////////////////////////////////////////////////////////
#include "upper_lower_case.hpp"

///////////////////////////////////////////////////////////////////////////////
//  directives related to delimiting generators 
//  delimit[...] and verbatim[...]
///////////////////////////////////////////////////////////////////////////////
#include "verbatim.hpp"
#include "delimit.hpp"
#include "no_delimit.hpp"

///////////////////////////////////////////////////////////////////////////////
//  repeat directives
//  repeat[...]
///////////////////////////////////////////////////////////////////////////////
#include "repeat.hpp"

///////////////////////////////////////////////////////////////////////////////
//  omit, skip, and duplicate directives
//  omit[...], skip[...], duplicate[...]
///////////////////////////////////////////////////////////////////////////////
#include "omit.hpp"
#include "duplicate.hpp"

///////////////////////////////////////////////////////////////////////////////
//  buffer directive
//  buffer[...]
///////////////////////////////////////////////////////////////////////////////
#include "buffer.hpp"

///////////////////////////////////////////////////////////////////////////////
//  strict and relaxed directives
//  strict[...], relaxed[...]
///////////////////////////////////////////////////////////////////////////////
#include "strict_relaxed.hpp"

///////////////////////////////////////////////////////////////////////////////
//  as_string and as_wstring directives
//  as_string[...], as_wstring[...]
///////////////////////////////////////////////////////////////////////////////
#include "as.hpp"

#endif
