#ifndef FEARLESS_UNITS__MAGNITUDE_HPP
#define FEARLESS_UNITS__MAGNITUDE_HPP

namespace fearless { namespace units {

struct magnitude_base_dimension :
    boost::units::base_dimension<magnitude_base_dimension,1>
{};

typedef magnitude_base_dimension::dimension_type magnitude_dimension;

struct magnitude_base_unit :
  public boost::units::base_unit<magnitude_base_unit, magnitude_dimension, 1>
{
    static std::string name()   { return("magnitude"); }
    static std::string symbol() { return("m"); }
};

typedef boost::units::make_system<magnitude_base_unit>::type magnitude_system;

// Some confusion here because magnitude is the name of the dimension and the
// unit
typedef boost::units::unit<magnitude_dimension, magnitude_system> magnitude;

BOOST_UNITS_STATIC_CONSTANT(magnitudes,magnitude);

}}

#endif // FEARLESS_UNITS__MAGNITUDE_HPP
