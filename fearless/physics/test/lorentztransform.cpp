#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <fearless/units/zero.hpp>
#include <fearless/units/time.hpp>
#include <fearless/physics/conventionalreality.hpp>
#include <fearless/physics/lorentztransform.hpp>
#include <fearless/physics/displacement.hpp>

namespace fearless { namespace physics {

BOOST_AUTO_TEST_CASE(boost_transforms_sensibly_along_path)
{
  typedef ConventionalReality Reality;
  Velocity<double> const
    v{1*units::metre_per_second, units::zero, units::zero};
  auto const transform = LorentzTransform<Reality, double>::boost(v);
  Event<Reality, double> const origin{};
  units::quantity<units::time, double> const time = 2*units::seconds;
  Displacement<double> const position_after_t = v * time;
  Event<Reality, double> const event_after_t(time, position_after_t);
  auto position_in_other_frame = transform.apply(event_after_t);
  // In the other frame, this position should coincide with the observer, and
  // thus be at the spatial origin
  BOOST_CHECK_EQUAL(position_in_other_frame.spatial(), Displacement<double>());
}

}}

