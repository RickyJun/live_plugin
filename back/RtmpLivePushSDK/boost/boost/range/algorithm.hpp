///////////////////////////////////////////////////////////////////////////////
/// \file algorithm.hpp
///   Includes the range-based versions of the algorithms in the
///   C++ standard header file <algorithm>
//
/////////////////////////////////////////////////////////////////////////////

// Copyright 2009 Neil Groves.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Acknowledgements:
// This code uses combinations of ideas, techniques and code snippets
// from: Thorsten Ottosen, Eric Niebler, Jeremy Siek,
// and Vladimir Prus'
//
// The original mutating algorithms that served as the first version
// were originally written by Vladimir Prus'
// <ghost@cs.msu.su> code from Boost Wiki

#if defined(_MSC_VER) && _MSC_VER >= 1000
#pragma once
#endif

#ifndef BOOST_RANGE_ALGORITHM_HPP_INCLUDED_01012009
#define BOOST_RANGE_ALGORITHM_HPP_INCLUDED_01012009

#include "concepts.hpp"
#include "iterator_range.hpp"
#include "difference_type.hpp"
#include "range_return.hpp"
#include "iterator_traits.hpp"
#include "next_prior.hpp"
#include <algorithm>

// Non-mutating algorithms
#include "adjacent_find.hpp"
#include "count.hpp"
#include "count_if.hpp"
#include "equal.hpp"
#include "for_each.hpp"
#include "find.hpp"
#include "find_end.hpp"
#include "find_first_of.hpp"
#include "find_if.hpp"
#include "lexicographical_compare.hpp"
#include "mismatch.hpp"
#include "search.hpp"
#include "search_n.hpp"

// Mutating algorithms
#include "copy.hpp"
#include "copy_backward.hpp"
#include "fill.hpp"
#include "fill_n.hpp"
#include "generate.hpp"
#include "inplace_merge.hpp"
#include "merge.hpp"
#include "nth_element.hpp"
#include "partial_sort.hpp"
#include "partial_sort_copy.hpp"
#include "partition.hpp"
#include "random_shuffle.hpp"
#include "remove.hpp"
#include "remove_copy.hpp"
#include "remove_copy_if.hpp"
#include "remove_if.hpp"
#include "replace.hpp"
#include "replace_copy.hpp"
#include "replace_copy_if.hpp"
#include "replace_if.hpp"
#include "reverse.hpp"
#include "reverse_copy.hpp"
#include "rotate.hpp"
#include "rotate_copy.hpp"
#include "sort.hpp"
#include "stable_partition.hpp"
#include "stable_sort.hpp"
#include "transform.hpp"
#include "unique.hpp"
#include "unique_copy.hpp"

// Binary search
#include "binary_search.hpp"
#include "equal_range.hpp"
#include "lower_bound.hpp"
#include "upper_bound.hpp"

// Set operations of sorted ranges
#include "set_algorithm.hpp"

// Heap operations
#include "heap_algorithm.hpp"

// Minimum and Maximum
#include "max_element.hpp"
#include "min_element.hpp"

// Permutations
#include "permutation.hpp"

#endif // include guard

