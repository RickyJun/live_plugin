//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_PREPROCESSOR_HPP
#define BOOST_CONTAINER_DETAIL_PREPROCESSOR_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include "config_begin.hpp"

#ifndef BOOST_NO_RVALUE_REFERENCES
#include "stored_ref.hpp"
#endif   //#ifndef BOOST_NO_RVALUE_REFERENCES

#include "workaround.hpp"

#ifdef BOOST_CONTAINER_PERFECT_FORWARDING
//#error "This file is not needed when perfect forwarding is available"
#endif   //BOOST_CONTAINER_PERFECT_FORWARDING

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

#define BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS 10

//Note:
//We define template parameters as const references to
//be able to bind temporaries. After that we will un-const them.
//This cast is ugly but it is necessary until "perfect forwarding"
//is achieved in C++0x. Meanwhile, if we want to be able to
//bind rvalues with non-const references, we have to be ugly
#ifndef BOOST_NO_RVALUE_REFERENCES
   #define BOOST_CONTAINER_PP_PARAM_LIST(z, n, data) \
   BOOST_PP_CAT(P, n) && BOOST_PP_CAT(p, n) \
   //!
#else
   #define BOOST_CONTAINER_PP_PARAM_LIST(z, n, data) \
   const BOOST_PP_CAT(P, n) & BOOST_PP_CAT(p, n) \
   //!
#endif   //#ifndef BOOST_NO_RVALUE_REFERENCES

#define BOOST_CONTAINER_PP_CONST_REF_PARAM_LIST_Q(z, n, Data) \
const BOOST_PP_CAT(Q, n) & BOOST_PP_CAT(q, n) \
//!

#ifndef BOOST_NO_RVALUE_REFERENCES
   #define BOOST_CONTAINER_PP_PARAM(U, u) \
   U && u \
   //!
#else
   #define BOOST_CONTAINER_PP_PARAM(U, u) \
   const U & u \
   //!
#endif   //#ifndef BOOST_NO_RVALUE_REFERENCES

#ifndef BOOST_NO_RVALUE_REFERENCES

   #if defined(BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

   #define BOOST_CONTAINER_PP_PARAM_INIT(z, n, data) \
   BOOST_PP_CAT(m_p, n) (static_cast<BOOST_PP_CAT(P, n)>( BOOST_PP_CAT(p, n) ))           \

   #else //#if defined(BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

   #define BOOST_CONTAINER_PP_PARAM_INIT(z, n, data) \
   BOOST_PP_CAT(m_p, n) (::boost::forward< BOOST_PP_CAT(P, n) >( BOOST_PP_CAT(p, n) ))           \
   //!

   #endif   //BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES

#else //BOOST_NO_RVALUE_REFERENCES

   #define BOOST_CONTAINER_PP_PARAM_INIT(z, n, data) \
   BOOST_PP_CAT(m_p, n) (const_cast<BOOST_PP_CAT(P, n) &>(BOOST_PP_CAT(p, n))) \
   //!
#endif   //#ifndef BOOST_NO_RVALUE_REFERENCES

#ifndef BOOST_NO_RVALUE_REFERENCES

   #if defined(BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

      #define BOOST_CONTAINER_PP_PARAM_DEFINE(z, n, data)  \
      BOOST_PP_CAT(P, n) & BOOST_PP_CAT(m_p, n);            \
      //!

   #else //BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG

      #define BOOST_CONTAINER_PP_PARAM_DEFINE(z, n, data)  \
      BOOST_PP_CAT(P, n) && BOOST_PP_CAT(m_p, n);            \
      //!

   #endif //defined(BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

#else //BOOST_NO_RVALUE_REFERENCES

   #define BOOST_CONTAINER_PP_PARAM_DEFINE(z, n, data)  \
   BOOST_PP_CAT(P, n) & BOOST_PP_CAT(m_p, n);             \
   //!
#endif   //#ifndef BOOST_NO_RVALUE_REFERENCES

#if !defined(BOOST_NO_RVALUE_REFERENCES) && defined(BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

   #define BOOST_CONTAINER_PP_MEMBER_FORWARD(z, n, data) \
   ::boost::container::container_detail::stored_ref< BOOST_PP_CAT(P, n) >::forward( BOOST_PP_CAT(this->m_p, n) ) \
   //!

#else //!defined(BOOST_NO_RVALUE_REFERENCES) && defined(BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

   #define BOOST_CONTAINER_PP_MEMBER_FORWARD(z, n, data) \
   ::boost::forward< BOOST_PP_CAT(P, n) >( BOOST_PP_CAT(this->m_p, n) ) \
   //!

#endif   //!defined(BOOST_NO_RVALUE_REFERENCES) && defined(BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

#define BOOST_CONTAINER_PP_PARAM_INC(z, n, data)   \
  BOOST_PP_CAT(++this->m_p, n)                     \
//!

#define BOOST_CONTAINER_PP_IDENTITY(z, n, data) data


#define BOOST_CONTAINER_PP_PARAM_FORWARD(z, n, data) \
::boost::forward< BOOST_PP_CAT(P, n) >( BOOST_PP_CAT(p, n) ) \
//!

#define BOOST_CONTAINER_PP_DECLVAL(z, n, data) \
::boost::move_detail::declval< BOOST_PP_CAT(P, n) >() \
//!

#define BOOST_CONTAINER_PP_MEMBER_IT_FORWARD(z, n, data) \
BOOST_PP_CAT(*this->m_p, n) \
//!

#define BOOST_CONTAINER_PP_TEMPLATE_PARAM_VOID_DEFAULT(z, n, data)   \
  BOOST_PP_CAT(class P, n) = void                                    \
//!

#define BOOST_CONTAINER_PP_TEMPLATE_PARAM_WITH_DEFAULT(z, n, default_type) \
  BOOST_PP_CAT(class P, n) = default_type                                  \
//!

#define BOOST_CONTAINER_PP_STATIC_PARAM_REF_DECLARE(z, n, data) \
   static BOOST_PP_CAT(P, n) & BOOST_PP_CAT(p, n); \
//!

#define BOOST_CONTAINER_PP_PARAM_PASS(z, n, data) \
   BOOST_PP_CAT(p, n) \
//!

#define BOOST_CONTAINER_PP_FWD_TYPE(z, n, data) \
   typename ::boost::move_detail::forward_type< BOOST_PP_CAT(P, n) >::type \
//!

#include "config_end.hpp"

//#else

//#ifdef BOOST_CONTAINER_PERFECT_FORWARDING
//#error "This file is not needed when perfect forwarding is available"
//#endif   //BOOST_CONTAINER_PERFECT_FORWARDING

#endif //#ifndef BOOST_CONTAINER_DETAIL_PREPROCESSOR_HPP
