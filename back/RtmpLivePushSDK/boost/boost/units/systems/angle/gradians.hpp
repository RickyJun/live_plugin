// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_ANGLE_GRADIANS_HPP
#define BOOST_UNITS_ANGLE_GRADIANS_HPP

#include "cmath.hpp"

#include "conversion.hpp"
#include "quantity.hpp"
#include "static_constant.hpp"
#include "make_system.hpp"
#include "gradian.hpp"

namespace boost {

namespace units {

namespace gradian {

typedef make_system<boost::units::angle::gradian_base_unit>::type system;

typedef unit<dimensionless_type,system>         dimensionless;
typedef unit<plane_angle_dimension,system>      plane_angle;          ///< angle gradian unit constant

BOOST_UNITS_STATIC_CONSTANT(gradian,plane_angle);
BOOST_UNITS_STATIC_CONSTANT(gradians,plane_angle);

} // namespace gradian

} // namespace units

} // namespace boost

#endif // BOOST_UNITS_ANGLE_GRADIANS_HPP
