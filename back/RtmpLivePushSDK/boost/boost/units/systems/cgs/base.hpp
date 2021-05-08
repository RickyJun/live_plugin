// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_CGS_BASE_HPP
#define BOOST_UNITS_CGS_BASE_HPP

#include <string>

#include "static_constant.hpp"
#include "unit.hpp"
#include "make_system.hpp"

#include "centimeter.hpp"
#include "gram.hpp"
#include "second.hpp"
#include "biot.hpp"

namespace boost {

namespace units { 

namespace cgs {

/// placeholder class defining cgs unit system
typedef make_system<centimeter_base_unit, 
                    gram_base_unit, 
                    boost::units::si::second_base_unit,
                    biot_base_unit>::type system;

/// various unit typedefs for convenience
typedef unit<dimensionless_type,system>         dimensionless;

} // namespace cgs
                                                    
} // namespace units

} // namespace boost

#endif // BOOST_UNITS_CGS_BASE_HPP
