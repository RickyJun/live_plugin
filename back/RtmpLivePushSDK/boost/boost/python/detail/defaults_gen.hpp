///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002, Joel de Guzman, 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEFAULTS_GEN_JDG20020807_HPP
#define DEFAULTS_GEN_JDG20020807_HPP

#include "preprocessor.hpp"
#include "repeat.hpp"
#include "repeat_from_to.hpp"
#include "enum.hpp"
#include "enum_params.hpp"
#include "enum_binary_params.hpp"
#include "tuple.hpp"
#include "cat.hpp"
#include "sub.hpp"
#include "stringize.hpp"
#include "inc.hpp"
#include "empty.hpp"
#include "comma_if.hpp"
#include "config.hpp"
#include "begin_end.hpp"
#include "next.hpp"
#include "deref.hpp"
#include <cstddef>

namespace boost { namespace python {

namespace detail
{
  // overloads_base is used as a base class for all function
  // stubs. This class holds the doc_string of the stubs.
  struct overloads_base
  {
      overloads_base(char const* doc_)
          : m_doc(doc_) {}

      overloads_base(char const* doc_, detail::keyword_range const& kw)
          : m_doc(doc_), m_keywords(kw) {}

      char const* doc_string() const
      {
          return m_doc;
      }

      detail::keyword_range const& keywords() const
      {
          return m_keywords;
      }

   private:
      char const* m_doc;
      detail::keyword_range m_keywords;
  };

  // overloads_proxy is generated by the overloads_common operator[] (see
  // below). This class holds a user defined call policies of the stubs.
  template <class CallPoliciesT, class OverloadsT>
  struct overloads_proxy
      : public overloads_base
  {
      typedef typename OverloadsT::non_void_return_type   non_void_return_type;
      typedef typename OverloadsT::void_return_type       void_return_type;

      overloads_proxy(
          CallPoliciesT const& policies_
          , char const* doc
          , keyword_range const& kw
          )
          : overloads_base(doc, kw)
            , policies(policies_)
      {}

      CallPoliciesT
      call_policies() const
      {
          return policies;
      }

      CallPoliciesT policies;
  };

  // overloads_common is our default function stubs base class. This
  // class returns the default_call_policies in its call_policies()
  // member function.  It can generate a overloads_proxy however through
  // its operator[]
  template <class DerivedT>
  struct overloads_common
      : public overloads_base
  {
      overloads_common(char const* doc)
          : overloads_base(doc) {}

      overloads_common(char const* doc, keyword_range const& kw)
          : overloads_base(doc, kw) {}

      default_call_policies
      call_policies() const
      {
          return default_call_policies();
      }

      template <class CallPoliciesT>
      overloads_proxy<CallPoliciesT, DerivedT>
      operator[](CallPoliciesT const& policies) const
      {
          return overloads_proxy<CallPoliciesT, DerivedT>(
              policies, this->doc_string(), this->keywords());
      }
  };

}}} // namespace boost::python::detail


#define BOOST_PYTHON_TYPEDEF_GEN(z, index, data)                                \
    typedef typename ::boost::mpl::next<BOOST_PP_CAT(iter, index)>::type        \
        BOOST_PP_CAT(iter, BOOST_PP_INC(index));                                \
    typedef typename ::boost::mpl::deref<BOOST_PP_CAT(iter, index)>::type       \
        BOOST_PP_CAT(T, index);

#define BOOST_PYTHON_FUNC_WRAPPER_GEN(z, index, data)                   \
    static RT BOOST_PP_CAT(func_,                                       \
        BOOST_PP_SUB_D(1, index, BOOST_PP_TUPLE_ELEM(3, 1, data))) (    \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(                                  \
            1, index, T, arg))                                          \
    {                                                                   \
        BOOST_PP_TUPLE_ELEM(3, 2, data)                                 \
        BOOST_PP_TUPLE_ELEM(3, 0, data)(                                \
            BOOST_PP_ENUM_PARAMS(                                       \
                index,                                                  \
                arg));                                                  \
    }

#define BOOST_PYTHON_GEN_FUNCTION(fname, fstubs_name, n_args, n_dflts, ret)     \
    struct fstubs_name                                                          \
    {                                                                           \
        BOOST_STATIC_CONSTANT(int, n_funcs = BOOST_PP_INC(n_dflts));            \
        BOOST_STATIC_CONSTANT(int, max_args = n_funcs);                         \
                                                                                \
        template <typename SigT>                                                \
        struct gen                                                              \
        {                                                                       \
            typedef typename ::boost::mpl::begin<SigT>::type rt_iter;           \
            typedef typename ::boost::mpl::deref<rt_iter>::type RT;             \
            typedef typename ::boost::mpl::next<rt_iter>::type iter0;           \
                                                                                \
            BOOST_PP_REPEAT_2ND(                                                \
                n_args,                                                         \
                BOOST_PYTHON_TYPEDEF_GEN,                                       \
                0)                                                              \
                                                                                \
            BOOST_PP_REPEAT_FROM_TO_2(                                          \
                BOOST_PP_SUB_D(1, n_args, n_dflts),                             \
                BOOST_PP_INC(n_args),                                           \
                BOOST_PYTHON_FUNC_WRAPPER_GEN,                                  \
                (fname, BOOST_PP_SUB_D(1, n_args, n_dflts), ret))               \
        };                                                                      \
    };                                                                          \

///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_MEM_FUNC_WRAPPER_GEN(z, index, data)                       \
    static RT BOOST_PP_CAT(func_,                                               \
        BOOST_PP_SUB_D(1, index, BOOST_PP_TUPLE_ELEM(3, 1, data))) (            \
            ClassT obj BOOST_PP_COMMA_IF(index)                                 \
            BOOST_PP_ENUM_BINARY_PARAMS_Z(1, index, T, arg)                     \
        )                                                                       \
    {                                                                           \
        BOOST_PP_TUPLE_ELEM(3, 2, data) obj.BOOST_PP_TUPLE_ELEM(3, 0, data)(    \
            BOOST_PP_ENUM_PARAMS(index, arg)                                    \
        );                                                                      \
    }

#define BOOST_PYTHON_GEN_MEM_FUNCTION(fname, fstubs_name, n_args, n_dflts, ret) \
    struct fstubs_name                                                          \
    {                                                                           \
        BOOST_STATIC_CONSTANT(int, n_funcs = BOOST_PP_INC(n_dflts));            \
        BOOST_STATIC_CONSTANT(int, max_args = n_funcs + 1);                     \
                                                                                \
        template <typename SigT>                                                \
        struct gen                                                              \
        {                                                                       \
            typedef typename ::boost::mpl::begin<SigT>::type rt_iter;           \
            typedef typename ::boost::mpl::deref<rt_iter>::type RT;             \
                                                                                \
            typedef typename ::boost::mpl::next<rt_iter>::type class_iter;      \
            typedef typename ::boost::mpl::deref<class_iter>::type ClassT;      \
            typedef typename ::boost::mpl::next<class_iter>::type iter0;        \
                                                                                \
            BOOST_PP_REPEAT_2ND(                                                \
                n_args,                                                         \
                BOOST_PYTHON_TYPEDEF_GEN,                                       \
                0)                                                              \
                                                                                \
            BOOST_PP_REPEAT_FROM_TO_2(                                          \
                BOOST_PP_SUB_D(1, n_args, n_dflts),                             \
                BOOST_PP_INC(n_args),                                           \
                BOOST_PYTHON_MEM_FUNC_WRAPPER_GEN,                              \
                (fname, BOOST_PP_SUB_D(1, n_args, n_dflts), ret))               \
        };                                                                      \
    };

#define BOOST_PYTHON_OVERLOAD_CONSTRUCTORS(fstubs_name, n_args, n_dflts)                    \
    fstubs_name(char const* doc = 0)                                                        \
        : ::boost::python::detail::overloads_common<fstubs_name>(doc) {}                    \
    template <std::size_t N>                                                                \
    fstubs_name(char const* doc, ::boost::python::detail::keywords<N> const& keywords)      \
        : ::boost::python::detail::overloads_common<fstubs_name>(                           \
            doc, keywords.range())                                                          \
    {                                                                                       \
        typedef typename ::boost::python::detail::                                          \
            error::more_keywords_than_function_arguments<                                   \
                N,n_args>::too_many_keywords assertion;                                     \
    }                                                                                       \
    template <std::size_t N>                                                                \
    fstubs_name(::boost::python::detail::keywords<N> const& keywords, char const* doc = 0)  \
        : ::boost::python::detail::overloads_common<fstubs_name>(                           \
            doc, keywords.range())                                                          \
    {                                                                                       \
        typedef typename ::boost::python::detail::                                          \
            error::more_keywords_than_function_arguments<                                   \
                N,n_args>::too_many_keywords assertion;                                     \
    }

# if defined(BOOST_NO_VOID_RETURNS)

#  define BOOST_PYTHON_GEN_FUNCTION_STUB(fname, fstubs_name, n_args, n_dflts)   \
    struct fstubs_name                                                          \
        : public ::boost::python::detail::overloads_common<fstubs_name>         \
    {                                                                           \
        BOOST_PYTHON_GEN_FUNCTION(                                              \
            fname, non_void_return_type, n_args, n_dflts, return)               \
        BOOST_PYTHON_GEN_FUNCTION(                                              \
            fname, void_return_type, n_args, n_dflts, ;)                        \
                                                                                \
        BOOST_PYTHON_OVERLOAD_CONSTRUCTORS(fstubs_name, n_args, n_dflts)        \
    };

#  define BOOST_PYTHON_GEN_MEM_FUNCTION_STUB(fname, fstubs_name, n_args, n_dflts)       \
    struct fstubs_name                                                                  \
        : public ::boost::python::detail::overloads_common<fstubs_name>                 \
    {                                                                                   \
        BOOST_PYTHON_GEN_MEM_FUNCTION(                                                  \
            fname, non_void_return_type, n_args, n_dflts, return)                       \
        BOOST_PYTHON_GEN_MEM_FUNCTION(                                                  \
            fname, void_return_type, n_args, n_dflts, ;)                                \
                                                                                        \
        BOOST_PYTHON_OVERLOAD_CONSTRUCTORS(fstubs_name, n_args + 1, n_dflts)            \
    };

# else // !defined(BOOST_NO_VOID_RETURNS)

#  define BOOST_PYTHON_GEN_FUNCTION_STUB(fname, fstubs_name, n_args, n_dflts)   \
    struct fstubs_name                                                          \
        : public ::boost::python::detail::overloads_common<fstubs_name>         \
    {                                                                           \
        BOOST_PYTHON_GEN_FUNCTION(                                              \
            fname, non_void_return_type, n_args, n_dflts, return)               \
                                                                                \
        typedef non_void_return_type void_return_type;                          \
        BOOST_PYTHON_OVERLOAD_CONSTRUCTORS(fstubs_name, n_args, n_dflts)        \
    };


#  define BOOST_PYTHON_GEN_MEM_FUNCTION_STUB(fname, fstubs_name, n_args, n_dflts)       \
    struct fstubs_name                                                                  \
        : public ::boost::python::detail::overloads_common<fstubs_name>                 \
    {                                                                                   \
        BOOST_PYTHON_GEN_MEM_FUNCTION(                                                  \
            fname, non_void_return_type, n_args, n_dflts, return)                       \
                                                                                        \
        typedef non_void_return_type void_return_type;                                  \
        BOOST_PYTHON_OVERLOAD_CONSTRUCTORS(fstubs_name, n_args + 1, n_dflts)            \
    };

# endif // !defined(BOOST_NO_VOID_RETURNS)

///////////////////////////////////////////////////////////////////////////////
//
//  MAIN MACROS
//
//      Given generator_name, fname, min_args and max_args, These macros
//      generate function stubs that forward to a function or member function
//      named fname. max_args is the arity of the function or member function
//      fname. fname can have default arguments. min_args is the minimum
//      arity that fname can accept.
//
//      There are two versions:
//
//          1. BOOST_PYTHON_FUNCTION_OVERLOADS for free functions
//          2. BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS for member functions.
//
//      For instance, given a function:
//
//      int
//      foo(int a, char b = 1, unsigned c = 2, double d = 3)
//      {
//          return a + b + c + int(d);
//      }
//
//      The macro invocation:
//
//          BOOST_PYTHON_FUNCTION_OVERLOADS(foo_stubs, foo, 1, 4)
//
//      Generates this code:
//
//      struct foo_stubsNonVoid
//      {
//          static const int n_funcs = 4;
//          static const int max_args = n_funcs;
//
//          template <typename SigT>
//          struct gen
//          {
//              typedef typename ::boost::mpl::begin<SigT>::type    rt_iter;
//              typedef typename rt_iter::type                      RT;
//              typedef typename rt_iter::next                      iter0;
//              typedef typename iter0::type                        T0;
//              typedef typename iter0::next                        iter1;
//              typedef typename iter1::type                        T1;
//              typedef typename iter1::next                        iter2;
//              typedef typename iter2::type                        T2;
//              typedef typename iter2::next                        iter3;
//              typedef typename iter3::type                        T3;
//              typedef typename iter3::next                        iter4;
//
//              static RT func_0(T0 arg0)
//              { return foo(arg0); }
//
//              static RT func_1(T0 arg0, T1 arg1)
//              { return foo(arg0, arg1); }
//
//              static RT func_2(T0 arg0, T1 arg1, T2 arg2)
//              { return foo(arg0, arg1, arg2); }
//
//              static RT func_3(T0 arg0, T1 arg1, T2 arg2, T3 arg3)
//              { return foo(arg0, arg1, arg2, arg3); }
//          };
//      };
//
//      struct foo_overloads
//          : public boost::python::detail::overloads_common<foo_overloads>
//      {
//          typedef foo_overloadsNonVoid    non_void_return_type;
//          typedef foo_overloadsNonVoid    void_return_type;
//
//          foo_overloads(char const* doc = 0)
//             : boost::python::detail::overloads_common<foo_overloads>(doc) {}
//      };
//
//      The typedefs non_void_return_type and void_return_type are
//      used to handle compilers that do not support void returns. The
//      example above typedefs non_void_return_type and
//      void_return_type to foo_overloadsNonVoid. On compilers that do
//      not support void returns, there are two versions:
//      foo_overloadsNonVoid and foo_overloadsVoid.  The "Void"
//      version is almost identical to the "NonVoid" version except
//      for the return type (void) and the lack of the return keyword.
//
//      See the overloads_common above for a description of the
//      foo_overloads' base class.
//
///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_FUNCTION_OVERLOADS(generator_name, fname, min_args, max_args)          \
    BOOST_PYTHON_GEN_FUNCTION_STUB(                                                         \
        fname,                                                                              \
        generator_name,                                                                     \
        max_args,                                                                           \
        BOOST_PP_SUB_D(1, max_args, min_args))

#define BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(generator_name, fname, min_args, max_args)   \
    BOOST_PYTHON_GEN_MEM_FUNCTION_STUB(                                                     \
        fname,                                                                              \
        generator_name,                                                                     \
        max_args,                                                                           \
        BOOST_PP_SUB_D(1, max_args, min_args))

// deprecated macro names (to be removed)
#define BOOST_PYTHON_FUNCTION_GENERATOR BOOST_PYTHON_FUNCTION_OVERLOADS
#define BOOST_PYTHON_MEM_FUN_GENERATOR BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS

///////////////////////////////////////////////////////////////////////////////
#endif // DEFAULTS_GEN_JDG20020807_HPP


