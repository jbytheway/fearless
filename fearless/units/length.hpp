#ifndef FEARLESS_UNITS__LENGTH_HPP
#define FEARLESS_UNITS__LENGTH_HPP

#include <boost/units/systems/si/length.hpp>
#include <boost/units/base_units/astronomical/light_year.hpp>
#include <boost/units/base_units/astronomical/parsec.hpp>

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

typedef boost::units::make_system<
    boost::units::astronomical::parsec_base_unit
  >::type parsec_system;

typedef boost::units::unit<boost::units::length_dimension,parsec_system>
  parsec_length;

BOOST_UNITS_STATIC_CONSTANT(parsec,parsec_length);
BOOST_UNITS_STATIC_CONSTANT(parsecs,parsec_length);

}}

#endif // FEARLESS_UNITS__LENGTH_HPP

