/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001-2003 Daniel Nuffer
    Copyright (c) 2001-2003 Hartmut Kaiser
    Copyright (c) 2002-2003 Martin Wille
    Copyright (c) 2002 Raghavendra Satish
    Copyright (c) 2001 Bruce Florman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CORE_MAIN_HPP)
#define BOOST_SPIRIT_CORE_MAIN_HPP

#include "version.hpp"
#include "debug.hpp"

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit.Core includes
//
///////////////////////////////////////////////////////////////////////////////

//  Spirit.Core.Kernel
#include "config.hpp"
#include "nil.hpp"
#include "match.hpp"
#include "parser.hpp"

//  Spirit.Core.Primitives
#include "primitives.hpp"
#include "numerics.hpp"

//  Spirit.Core.Scanner
#include "scanner.hpp"
#include "skipper.hpp"

//  Spirit.Core.NonTerminal
#include "subrule.hpp"
#include "rule.hpp"
#include "grammar.hpp"

//  Spirit.Core.Composite
#include "actions.hpp"
#include "composite.hpp"
#include "directives.hpp"
#include "epsilon.hpp"
#include "sequence.hpp"
#include "sequential_and.hpp"
#include "sequential_or.hpp"
#include "alternative.hpp"
#include "difference.hpp"
#include "intersection.hpp"
#include "exclusive_or.hpp"
#include "kleene_star.hpp"
#include "positive.hpp"
#include "optional.hpp"
#include "list.hpp"
#include "no_actions.hpp"

//  Deprecated interface includes
#include "assign_actor.hpp"
#include "push_back_actor.hpp"

#if defined(BOOST_SPIRIT_DEBUG)
    //////////////////////////////////
    #include "parser_names.hpp"

#endif // BOOST_SPIRIT_DEBUG

#endif // BOOST_SPIRIT_CORE_MAIN_HPP

