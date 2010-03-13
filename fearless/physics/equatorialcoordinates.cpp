#include <fearless/physics/equatorialcoordinates.hpp>

#include <fearless/maths/specialorthogonalmatrix.hpp>

namespace fearless { namespace physics {

namespace {
  units::quantity<units::radian_angle, double> const
    J2000Obliquity(23.4392911*units::degrees);
  maths::Matrix3<double> equatorialToCelestial =
    maths::SpecialOrthogonalMatrix<double>::x_rotation(J2000Obliquity).
    to_matrix();
}

template<>
Displacement<double>
EquatorialCoordinates<double>::to_celestial_cartesian() const
{
  typedef units::quantity<units::radian_angle, double> Angle;
  Angle theta = right_ascension + M_PI * units::radians;
  Angle phi = declination - M_PI/2 * units::radians;;
  typedef units::quantity<units::length, double> Distance;
  Distance x = cos(theta) * sin(phi) * distance;
  Distance y = cos(phi) * distance;
  Distance z = -sin(theta) * sin(phi) * distance;

  return (Displacement<double>(x, y, z) * equatorialToCelestial);
}

template<>
Displacement<float>
EquatorialCoordinates<float>::to_celestial_cartesian() const
{
  FEARLESS_FATAL("not implemented");
}

}}

