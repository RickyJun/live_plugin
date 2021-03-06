// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2007-8 Anthony Williams
// (C) Copyright 2011-2012 Vicente J. Botet Escriba

#ifndef BOOST_THREAD_MOVE_HPP
#define BOOST_THREAD_MOVE_HPP

#include "config.hpp"
#ifndef BOOST_NO_SFINAE
#include "enable_if.hpp"
#include "is_convertible.hpp"
#include "remove_reference.hpp"
#include "remove_cv.hpp"
#include "decay.hpp"
#endif

#include "delete.hpp"
#include "move.hpp"
#include "abi_prefix.hpp"

namespace boost
{

    namespace detail
    {
      template <typename T>
      struct has_move_emulation_enabled_aux_dummy_specialization;
        template<typename T>
        struct thread_move_t
        {
            T& t;
            explicit thread_move_t(T& t_):
                t(t_)
            {}

            T& operator*() const
            {
                return t;
            }

            T* operator->() const
            {
                return &t;
            }
        private:
            void operator=(thread_move_t&);
        };
    }


#ifndef BOOST_NO_SFINAE
    template<typename T>
    typename enable_if<boost::is_convertible<T&,boost::detail::thread_move_t<T> >, boost::detail::thread_move_t<T> >::type move(T& t)
    {
        return boost::detail::thread_move_t<T>(t);
    }
#endif

    template<typename T>
    boost::detail::thread_move_t<T> move(boost::detail::thread_move_t<T> t)
    {
        return t;
    }
}

#if ! defined  BOOST_NO_RVALUE_REFERENCES

#define BOOST_THREAD_RV_REF(TYPE) BOOST_RV_REF(TYPE)
#define BOOST_THREAD_RV_REF_BEG BOOST_RV_REF_BEG
#define BOOST_THREAD_RV_REF_END BOOST_RV_REF_END
#define BOOST_THREAD_RV(V) V
#define BOOST_THREAD_MAKE_RV_REF(RVALUE) RVALUE
#define BOOST_THREAD_FWD_REF(TYPE) BOOST_FWD_REF(TYPE)
#define BOOST_THREAD_DCL_MOVABLE(TYPE)
#define BOOST_THREAD_DCL_MOVABLE_BEG(T) \
  namespace detail { \
    template <typename T> \
    struct has_move_emulation_enabled_aux_dummy_specialization<

#define BOOST_THREAD_DCL_MOVABLE_END > \
      : integral_constant<bool, true> \
      {}; \
    }

#elif ! defined  BOOST_NO_RVALUE_REFERENCES && defined  BOOST_MSVC

#define BOOST_THREAD_RV_REF(TYPE) BOOST_RV_REF(TYPE)
#define BOOST_THREAD_RV_REF_BEG BOOST_RV_REF_BEG
#define BOOST_THREAD_RV_REF_END BOOST_RV_REF_END
#define BOOST_THREAD_RV(V) V
#define BOOST_THREAD_MAKE_RV_REF(RVALUE) RVALUE
#define BOOST_THREAD_FWD_REF(TYPE) BOOST_FWD_REF(TYPE)
#define BOOST_THREAD_DCL_MOVABLE(TYPE)
#define BOOST_THREAD_DCL_MOVABLE_BEG(T) \
  namespace detail { \
    template <typename T> \
    struct has_move_emulation_enabled_aux_dummy_specialization<

#define BOOST_THREAD_DCL_MOVABLE_END > \
      : integral_constant<bool, true> \
      {}; \
    }

#else

#if defined BOOST_THREAD_USES_MOVE
#define BOOST_THREAD_RV_REF(TYPE) BOOST_RV_REF(TYPE)
#define BOOST_THREAD_RV_REF_BEG BOOST_RV_REF_BEG
#define BOOST_THREAD_RV_REF_END BOOST_RV_REF_END
#define BOOST_THREAD_RV(V) V
#define BOOST_THREAD_FWD_REF(TYPE) BOOST_FWD_REF(TYPE)
#define BOOST_THREAD_DCL_MOVABLE(TYPE)
#define BOOST_THREAD_DCL_MOVABLE_BEG(T) \
  namespace detail { \
    template <typename T> \
    struct has_move_emulation_enabled_aux_dummy_specialization<

#define BOOST_THREAD_DCL_MOVABLE_END > \
      : integral_constant<bool, true> \
      {}; \
    }

#else

#define BOOST_THREAD_RV_REF(TYPE) boost::detail::thread_move_t< TYPE >
#define BOOST_THREAD_RV_REF_BEG boost::detail::thread_move_t<
#define BOOST_THREAD_RV_REF_END >
#define BOOST_THREAD_RV(V) (*V)
#define BOOST_THREAD_FWD_REF(TYPE) BOOST_FWD_REF(TYPE)

#define BOOST_THREAD_DCL_MOVABLE(TYPE) \
template <> \
struct has_move_emulation_enabled_aux< TYPE > \
  : BOOST_MOVE_BOOST_NS::integral_constant<bool, true> \
{};

#define BOOST_THREAD_DCL_MOVABLE_BEG(T) \
template <typename T> \
struct has_move_emulation_enabled_aux<

#define BOOST_THREAD_DCL_MOVABLE_END > \
  : BOOST_MOVE_BOOST_NS::integral_constant<bool, true> \
{};

#endif

namespace boost
{
namespace detail
{
  template <typename T>
  BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type)
  make_rv_ref(T v)  BOOST_NOEXCEPT
  {
    return (BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type))(v);
  }
//  template <typename T>
//  BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type)
//  make_rv_ref(T &v)  BOOST_NOEXCEPT
//  {
//    return (BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type))(v);
//  }
//  template <typename T>
//  const BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type)
//  make_rv_ref(T const&v)  BOOST_NOEXCEPT
//  {
//    return (const BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type))(v);
//  }
}
}

#define BOOST_THREAD_MAKE_RV_REF(RVALUE) RVALUE.move()
//#define BOOST_THREAD_MAKE_RV_REF(RVALUE) boost::detail::make_rv_ref(RVALUE)
#endif


#if ! defined  BOOST_NO_RVALUE_REFERENCES

#define BOOST_THREAD_MOVABLE(TYPE)

#else

#if defined BOOST_THREAD_USES_MOVE

#define BOOST_THREAD_MOVABLE(TYPE) \
    ::boost::rv<TYPE>& move()  BOOST_NOEXCEPT \
    { \
      return *static_cast< ::boost::rv<TYPE>* >(this); \
    } \
    const ::boost::rv<TYPE>& move() const BOOST_NOEXCEPT \
    { \
      return *static_cast<const ::boost::rv<TYPE>* >(this); \
    } \
    operator ::boost::rv<TYPE>&() \
    { \
      return *static_cast< ::boost::rv<TYPE>* >(this); \
    } \
    operator const ::boost::rv<TYPE>&() const \
    { \
      return *static_cast<const ::boost::rv<TYPE>* >(this); \
    }\

#else

#define BOOST_THREAD_MOVABLE(TYPE) \
    operator ::boost::detail::thread_move_t<TYPE>() BOOST_NOEXCEPT \
    { \
        return move(); \
    } \
    ::boost::detail::thread_move_t<TYPE> move() BOOST_NOEXCEPT \
    { \
      ::boost::detail::thread_move_t<TYPE> x(*this); \
        return x; \
    } \

#endif
#endif

#define BOOST_THREAD_MOVABLE_ONLY(TYPE) \
  BOOST_THREAD_NO_COPYABLE(TYPE) \
  BOOST_THREAD_MOVABLE(TYPE) \

#define BOOST_THREAD_COPYABLE_AND_MOVABLE(TYPE) \
  BOOST_THREAD_MOVABLE(TYPE) \



#ifndef BOOST_NO_RVALUE_REFERENCES
namespace boost
{  namespace thread_detail
  {
      template <class T>
      typename decay<T>::type
      decay_copy(T&& t)
      {
          return boost::forward<T>(t);
      }
  }
}
#endif

#include "abi_suffix.hpp"

#endif
