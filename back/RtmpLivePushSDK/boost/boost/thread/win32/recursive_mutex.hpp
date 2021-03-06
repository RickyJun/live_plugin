#ifndef BOOST_RECURSIVE_MUTEX_WIN32_HPP
#define BOOST_RECURSIVE_MUTEX_WIN32_HPP

//  recursive_mutex.hpp
//
//  (C) Copyright 2006-7 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#include "basic_recursive_mutex.hpp"
#include "exceptions.hpp"
#include "locks.hpp"

#include "abi_prefix.hpp"

namespace boost
{
    class recursive_mutex:
        public ::boost::detail::basic_recursive_mutex
    {
    public:
        BOOST_THREAD_NO_COPYABLE(recursive_mutex)
        recursive_mutex()
        {
            ::boost::detail::basic_recursive_mutex::initialize();
        }
        ~recursive_mutex()
        {
            ::boost::detail::basic_recursive_mutex::destroy();
        }

        typedef unique_lock<recursive_mutex> scoped_lock;
        typedef detail::try_lock_wrapper<recursive_mutex> scoped_try_lock;
    };

    typedef recursive_mutex recursive_try_mutex;

    class recursive_timed_mutex:
        public ::boost::detail::basic_recursive_timed_mutex
    {
    public:
        BOOST_THREAD_NO_COPYABLE(recursive_timed_mutex)
        recursive_timed_mutex()
        {
            ::boost::detail::basic_recursive_timed_mutex::initialize();
        }
        ~recursive_timed_mutex()
        {
            ::boost::detail::basic_recursive_timed_mutex::destroy();
        }

        typedef unique_lock<recursive_timed_mutex> scoped_timed_lock;
        typedef detail::try_lock_wrapper<recursive_timed_mutex> scoped_try_lock;
        typedef scoped_timed_lock scoped_lock;
    };
}

#include "abi_suffix.hpp"

#endif
