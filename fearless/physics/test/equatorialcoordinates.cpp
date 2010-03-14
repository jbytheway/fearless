#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <fearless/maths/check_very_near.hpp>
#include <fearless/physics/equatorialcoordinates.hpp>

namespace fearless { namespace physics {

BOOST_AUTO_TEST_CASE(alpha_centauri_position_transforms)
{
  // Check the transform for the particular case of Alpha Centauri
  typedef units::quantity<units::radian_angle> Angle;
  typedef units::quantity<units::length> Length;
  Angle ra(219.914124599*units::degrees);
  Angle declination(-60.839480464*units::degrees);
  Length distance(4.092845*units::light_years);
  Length x(-1.52962028*units::light_years);
  Length y(-2.77018523*units::light_years);
  Length z(2.59571099*units::light_years);
  EquatorialCoordinates<double> eq(ra, declination, distance);
  FEARLESS_MATHS_CHECK_VERY_NEAR(
      eq.to_celestial_cartesian(),
      Displacement<double>(x, y, z)
    );
}

}}

