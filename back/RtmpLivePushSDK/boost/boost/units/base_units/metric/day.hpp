// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2007-2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNIT_SYSTEMS_OTHER_DAY_HPP_INCLUDED
#define BOOST_UNIT_SYSTEMS_OTHER_DAY_HPP_INCLUDED

#include "scaled_base_unit.hpp"
#include "static_rational.hpp"
#include "scale.hpp"
#include "second.hpp"

namespace boost {

namespace units {

namespace metric {

typedef scaled_base_unit<boost::units::si::second_base_unit, scale<86400, static_rational<1> > > day_base_unit;

} // namespace metric

template<>
struct base_unit_info<metric::day_base_unit> {
    static const char* name()   { return("day"); }
    static const char* symbol() { return("d"); }
};

} // namespace units

} // namespace boost

#endif