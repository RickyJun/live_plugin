//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_PREPROCESSOR_HPP
#define BOOST_INTRUSIVE_DETAIL_PREPROCESSOR_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include "config_begin.hpp"
#include "workaround.hpp"

#include "local.hpp"
#include "paren_if.hpp"
#include "comma_if.hpp"
#include "expr_if.hpp"
#include "cat.hpp"
#include "enum.hpp"
#include "enum_params.hpp"
#include "enum_trailing_params.hpp"
#include "enum_trailing.hpp"
#include "enum_shifted_params.hpp"
#include "enum_shifted.hpp"
#include "repeat.hpp"
#include "not.hpp"
#include "sub.hpp"
#include "add.hpp"
#include "iterate.hpp"

#define BOOST_INTRUSIVE_MAX_CONSTRUCTOR_PARAMETERS 10

#define BOOST_INTRUSIVE_PP_IDENTITY(z, n, data) data

#define BOOST_INTRUSIVE_PP_DECLVAL(z, n, data) \
boost::move_detail::declval< BOOST_PP_CAT(P, n) >() \
//!

#define BOOST_INTRUSIVE_PP_TEMPLATE_PARAM_VOID_DEFAULT(z, n, data)   \
  BOOST_PP_CAT(class P, n) = void                                      \
//!

#include "config_end.hpp"

#endif //#ifndef BOOST_INTRUSIVE_DETAIL_PREPROCESSOR_HPP
