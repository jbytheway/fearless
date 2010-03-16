#ifndef FEARLESS_PHYSICS__EQUATORIALCOORDINATES_HPP
#define FEARLESS_PHYSICS__EQUATORIALCOORDINATES_HPP

#include <type_traits>

#include <fearless/units/quantity.hpp>
#include <fearless/units/angle.hpp>
#include <fearless/units/length.hpp>
#include <fearless/physics/api.hpp>
#include <fearless/physics/displacement.hpp>

namespace fearless { namespace physics {

template<typename T>
struct FEARLESS_PHYSICS_API EquatorialCoordinates {
  BOOST_MPL_ASSERT((std::is_floating_point<T>));

  EquatorialCoordinates(
      units::quantity<units::radian_angle, T> ra,
      units::quantity<units::radian_angle, T> de,
      units::quantity<units::length, T> di
    ) :
    right_ascension(ra),
    declination(de),
    distance(di)
  {}

  units::quantity<units::radian_angle, T> right_ascension;
  units::quantity<units::radian_angle, T> declination;
  units::quantity<units::length, T> distance;

  // Defined in cpp file
  Displacement<T> to_celestial_cartesian() const;
};

}}

#endif // FEARLESS_PHYSICS__EQUATORIALCOORDINATES_HPP

