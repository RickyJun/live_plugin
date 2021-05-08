// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_SI_BASE_HPP
#define BOOST_UNITS_SI_BASE_HPP

#include <string>

#include "static_constant.hpp"
#include "unit.hpp"
#include "make_system.hpp"

#include "meter.hpp"
#include "kilogram.hpp"
#include "second.hpp"
#include "ampere.hpp"
#include "kelvin.hpp"
#include "mole.hpp"
#include "candela.hpp"
#include "radian.hpp"
#include "steradian.hpp"

namespace boost {

namespace units { 

namespace si {

/// placeholder class defining si unit system
typedef make_system<meter_base_unit, 
                    kilogram_base_unit, 
                    second_base_unit, 
                    ampere_base_unit,
                    kelvin_base_unit,
                    mole_base_unit,
                    candela_base_unit,
                    angle::radian_base_unit,
                    angle::steradian_base_unit>::type system;

/// dimensionless si unit
typedef unit<dimensionless_type,system>         dimensionless;

} // namespace si

} // namespace units

} // namespace boost

#endif // BOOST_UNITS_SI_BASE_HPP
