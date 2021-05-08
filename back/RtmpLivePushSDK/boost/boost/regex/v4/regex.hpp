/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex.cpp
  *   VERSION      see <boost/version.hpp"
  *   DESCRIPTION: Declares boost::basic_regex<> and associated
  *                functions and classes. This header is the main
  *                entry point for the template regex code.
  */

#ifndef BOOST_RE_REGEX_HPP_INCLUDED
#define BOOST_RE_REGEX_HPP_INCLUDED

#ifdef __cplusplus

// what follows is all C++ don't include in C builds!!

#ifndef BOOST_REGEX_CONFIG_HPP
#include "config.hpp"
#endif
#ifndef BOOST_REGEX_WORKAROUND_HPP
#include "regex_workaround.hpp"
#endif

#ifndef BOOST_REGEX_FWD_HPP
#include "regex_fwd.hpp"
#endif
#ifndef BOOST_REGEX_TRAITS_HPP
#include "regex_traits.hpp"
#endif
#ifndef BOOST_REGEX_RAW_BUFFER_HPP
#include "error_type.hpp"
#endif
#ifndef BOOST_REGEX_V4_MATCH_FLAGS
#include "match_flags.hpp"
#endif
#ifndef BOOST_REGEX_RAW_BUFFER_HPP
#include "regex_raw_buffer.hpp"
#endif
#ifndef BOOST_RE_PAT_EXCEPT_HPP
#include "pattern_except.hpp"
#endif

#ifndef BOOST_REGEX_V4_CHAR_REGEX_TRAITS_HPP
#include "char_regex_traits.hpp"
#endif
#ifndef BOOST_REGEX_V4_STATES_HPP
#include "states.hpp"
#endif
#ifndef BOOST_REGEX_V4_REGBASE_HPP
#include "regbase.hpp"
#endif
#ifndef BOOST_REGEX_V4_ITERATOR_TRAITS_HPP
#include "iterator_traits.hpp"
#endif
#ifndef BOOST_REGEX_V4_BASIC_REGEX_HPP
#include "basic_regex.hpp"
#endif
#ifndef BOOST_REGEX_V4_BASIC_REGEX_CREATOR_HPP
#include "basic_regex_creator.hpp"
#endif
#ifndef BOOST_REGEX_V4_BASIC_REGEX_PARSER_HPP
#include "basic_regex_parser.hpp"
#endif
#ifndef BOOST_REGEX_V4_SUB_MATCH_HPP
#include "sub_match.hpp"
#endif
#ifndef BOOST_REGEX_FORMAT_HPP
#include "regex_format.hpp"
#endif
#ifndef BOOST_REGEX_V4_MATCH_RESULTS_HPP
#include "match_results.hpp"
#endif
#ifndef BOOST_REGEX_V4_PROTECTED_CALL_HPP
#include "protected_call.hpp"
#endif
#ifndef BOOST_REGEX_MATCHER_HPP
#include "perl_matcher.hpp"
#endif
//
// template instances:
//
#define BOOST_REGEX_CHAR_T char
#ifdef BOOST_REGEX_NARROW_INSTANTIATE
#  define BOOST_REGEX_INSTANTIATE
#endif
#include "instances.hpp"
#undef BOOST_REGEX_CHAR_T
#ifdef BOOST_REGEX_INSTANTIATE
#  undef BOOST_REGEX_INSTANTIATE
#endif

#ifndef BOOST_NO_WREGEX
#define BOOST_REGEX_CHAR_T wchar_t
#ifdef BOOST_REGEX_WIDE_INSTANTIATE
#  define BOOST_REGEX_INSTANTIATE
#endif
#include "instances.hpp"
#undef BOOST_REGEX_CHAR_T
#ifdef BOOST_REGEX_INSTANTIATE
#  undef BOOST_REGEX_INSTANTIATE
#endif
#endif

#if !defined(BOOST_NO_WREGEX) && defined(BOOST_REGEX_HAS_OTHER_WCHAR_T)
#define BOOST_REGEX_CHAR_T unsigned short
#ifdef BOOST_REGEX_US_INSTANTIATE
#  define BOOST_REGEX_INSTANTIATE
#endif
#include "instances.hpp"
#undef BOOST_REGEX_CHAR_T
#ifdef BOOST_REGEX_INSTANTIATE
#  undef BOOST_REGEX_INSTANTIATE
#endif
#endif


namespace boost{
#ifdef BOOST_REGEX_NO_FWD
typedef basic_regex<char, regex_traits<char> > regex;
#ifndef BOOST_NO_WREGEX
typedef basic_regex<wchar_t, regex_traits<wchar_t> > wregex;
#endif
#endif

typedef match_results<const char*> cmatch;
typedef match_results<std::string::const_iterator> smatch;
#ifndef BOOST_NO_WREGEX
typedef match_results<const wchar_t*> wcmatch;
typedef match_results<std::wstring::const_iterator> wsmatch;
#endif

} // namespace boost
#ifndef BOOST_REGEX_MATCH_HPP
#include "regex_match.hpp"
#endif
#ifndef BOOST_REGEX_V4_REGEX_SEARCH_HPP
#include "regex_search.hpp"
#endif
#ifndef BOOST_REGEX_ITERATOR_HPP
#include "regex_iterator.hpp"
#endif
#ifndef BOOST_REGEX_TOKEN_ITERATOR_HPP
#include "regex_token_iterator.hpp"
#endif
#ifndef BOOST_REGEX_V4_REGEX_GREP_HPP
#include "regex_grep.hpp"
#endif
#ifndef BOOST_REGEX_V4_REGEX_REPLACE_HPP
#include "regex_replace.hpp"
#endif
#ifndef BOOST_REGEX_V4_REGEX_MERGE_HPP
#include "regex_merge.hpp"
#endif
#ifndef BOOST_REGEX_SPLIT_HPP
#include "regex_split.hpp"
#endif

#endif  // __cplusplus

#endif  // include































