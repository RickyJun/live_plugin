#ifndef BOOST_THREAD_THREAD_HPP
#define BOOST_THREAD_THREAD_HPP

//  thread.hpp
//
//  (C) Copyright 2007-8 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "platform.hpp"

#if defined(BOOST_THREAD_PLATFORM_WIN32)
#include "thread_data.hpp"
#elif defined(BOOST_THREAD_PLATFORM_PTHREAD)
#include "thread_data.hpp"
#else
#error "Boost threads unavailable on this platform"
#endif

#include "thread.hpp"
#include "thread_interruption.hpp"
#include "thread_group.hpp"
#include "thread.hpp"


#endif
