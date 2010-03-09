#ifndef FEARLESS_UNITS__LENGTH_HPP
#define FEARLESS_UNITS__LENGTH_HPP

#include <boost/units/systems/si/length.hpp>
#include <boost/units/base_units/astronomical/light_year.hpp>

namespace fearless { namespace units {

using boost::units::si::length;
using boost::units::si::metres;
using boost::units::si::metre;

typedef boost::units::make_system<
    boost::units::astronomical::light_year_base_unit
  >::type light_year_system;

typedef boost::units::unit<boost::units::length_dimension,light_year_system>
  light_year_length;

BOOST_UNITS_STATIC_CONSTANT(light_year,light_year_length);
BOOST_UNITS_STATIC_CONSTANT(light_years,light_year_length);

}}

#endif // FEARLESS_UNITS__LENGTH_HPP

