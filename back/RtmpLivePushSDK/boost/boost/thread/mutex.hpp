#ifndef BOOST_THREAD_MUTEX_HPP
#define BOOST_THREAD_MUTEX_HPP

//  mutex.hpp
//
//  (C) Copyright 2007 Anthony Williams 
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "platform.hpp"
#if defined(BOOST_THREAD_PLATFORM_WIN32)
#include "mutex.hpp"
#elif defined(BOOST_THREAD_PLATFORM_PTHREAD)
#include "mutex.hpp"
#else
#error "Boost threads unavailable on this platform"
#endif

#endif
