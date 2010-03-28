#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <fearless/physics/redshift.hpp>

#include <fearless/physics/conventionalreality.hpp>

namespace fearless { namespace physics {

typedef ConventionalReality Reality;
typedef Redshift<Reality, double> RS;

BOOST_AUTO_TEST_CASE(redshift_smoke_test)
{
  typedef units::quantity<units::velocity, double> Vel;
  Vel fast = Reality::c()/2.0;
  units::quantity<units::temperature, double> temp = 1.0*units::kelvin;

  // Moving directly towards yields blueshift
  RS directly_towards{fast, 1.0};
  BOOST_CHECK_GT(directly_towards.apply(temp), temp);

  // Moving directly away yields redshift
  RS directly_away{fast, -1.0};
  BOOST_CHECK_LT(directly_away.apply(temp), temp);

  // When visible directly beside it should be redshifted, because only time
  // dilation applies
  RS perpendicular{fast, 0.0};
  BOOST_CHECK_LT(perpendicular.apply(temp), temp);
}

}}

