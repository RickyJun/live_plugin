// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_HPP_27_07_04
#define BOOST_RANGE_HPP_27_07_04

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#if _MSC_VER == 1300 // experiment

#include "collection_traits.hpp"
#include "iterator_range.hpp"
#include "sub_range.hpp"

#else

#include "functions.hpp"
#include "metafunctions.hpp"
#include "iterator_range.hpp"
#include "sub_range.hpp"

#endif // _MSC_VER == 1300 // experiment

#endif
