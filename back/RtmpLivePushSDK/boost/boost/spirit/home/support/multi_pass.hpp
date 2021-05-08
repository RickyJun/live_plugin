//  Copyright (c) 2001-2009, Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_ITERATOR_MULTI_PASS_MAR_16_2007_0201AM)
#define BOOST_SPIRIT_ITERATOR_MULTI_PASS_MAR_16_2007_0201AM

#if defined(_MSC_VER)
#pragma once
#endif

//  Include everything needed for the multi_pass
//  Ownership policies
#include "first_owner_policy.hpp"
#include "ref_counted_policy.hpp"

//  Input policies
#include "input_iterator_policy.hpp"
#include "buffering_input_iterator_policy.hpp"
#include "istream_policy.hpp"
#include "lex_input_policy.hpp"
#include "split_functor_input_policy.hpp"
#include "functor_input_policy.hpp"

//  Checking policies
#include "buf_id_check_policy.hpp"
#include "no_check_policy.hpp"

//  Storage policies
#include "fixed_size_queue_policy.hpp"
#include "split_std_deque_policy.hpp"

//  Main multi_pass iterator 
#include "combine_policies.hpp"
#include "multi_pass.hpp"
#include "multi_pass.hpp"

#endif 
