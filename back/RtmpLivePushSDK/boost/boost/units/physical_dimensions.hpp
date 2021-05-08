// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2007-2010 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_PHYSICAL_UNITS_HPP
#define BOOST_UNITS_PHYSICAL_UNITS_HPP

///
/// \file
/// \brief Physical dimensions according to the SI system.
/// \details This header includes all physical dimension headers for both base
///   and derived dimensions.
///

// Include all of the physical_dimension headers.

// SI seven fundamental dimensions.
#include "amount.hpp"
#include "current.hpp"
#include "length.hpp"
#include "luminous_intensity.hpp"
#include "mass.hpp"
#include "temperature.hpp"
#include "time.hpp"

// Base dimensions are extended to include plane and solid angle for convenience.
#include "plane_angle.hpp"
#include "solid_angle.hpp"

// Derived dimensions.
#include "absorbed_dose.hpp"
#include "acceleration.hpp"
#include "action.hpp"
#include "activity.hpp"
#include "angular_acceleration.hpp"
#include "angular_momentum.hpp"
#include "angular_velocity.hpp"
#include "area.hpp"
#include "capacitance.hpp"
#include "conductance.hpp"
#include "conductivity.hpp"
#include "dose_equivalent.hpp"
#include "dynamic_viscosity.hpp"
#include "electric_charge.hpp"
#include "electric_potential.hpp"
#include "energy.hpp"
#include "energy_density.hpp"
#include "force.hpp"
#include "frequency.hpp"
#include "heat_capacity.hpp"
#include "illuminance.hpp"
#include "impedance.hpp"
#include "inductance.hpp"
#include "kinematic_viscosity.hpp"
#include "luminance.hpp"
#include "luminous_flux.hpp"
#include "magnetic_field_intensity.hpp"
#include "magnetic_flux.hpp"
#include "magnetic_flux_density.hpp"
#include "mass_density.hpp"
#include "molar_energy.hpp"
#include "molar_heat_capacity.hpp"
#include "moment_of_inertia.hpp"
#include "momentum.hpp"
#include "permeability.hpp"
#include "permittivity.hpp"
#include "power.hpp"
#include "pressure.hpp"
#include "reluctance.hpp"
#include "resistance.hpp"
#include "resistivity.hpp"
#include "specific_energy.hpp"
#include "specific_heat_capacity.hpp"
#include "specific_volume.hpp"
#include "stress.hpp"
#include "surface_density.hpp"
#include "surface_tension.hpp"
#include "thermal_conductivity.hpp"
#include "torque.hpp"
#include "velocity.hpp"
#include "volume.hpp"
#include "wavenumber.hpp"

#endif // BOOST_UNITS_PHYSICAL_UNITS_HPP
