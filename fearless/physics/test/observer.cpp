#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <fearless/physics/observer.hpp>

#include <fearless/physics/conventionalreality.hpp>
#include <fearless/physics/rootframe.hpp>

namespace fearless { namespace physics {

typedef ConventionalReality Reality;
typedef Observer<Reality> Obs;
typedef Event<Reality, double> Ev;
using std::cout;
using std::endl;

BOOST_AUTO_TEST_CASE(boost_moves_observer)
{
  auto rootFrame =
    std::shared_ptr<RootFrame<Reality>>(new RootFrame<Reality>("root"));
  Ev origin{};
  auto second = 1.0*units::second;
  Velocity<double> v{1.0*units::metre_per_second, units::zero, units::zero};
  Obs obs{RelativeInertialFrame<Reality>(rootFrame, "observer")};
  auto t0 = obs.make_transform_from(*rootFrame);
  auto p0 = t0.translation();
  // Nothing's happened yet, so obs is at origin
  BOOST_CHECK_EQUAL(origin, p0);

  obs.advance(second);
  auto t1 = obs.make_transform_from(*rootFrame);
  auto p1 = t1.inverse().translation();
  // Now spatial bit should still be the same
  BOOST_CHECK_EQUAL(origin.spatial(), p1.spatial());
  // But the observer should have moved forward in time
  BOOST_CHECK_GT(p1.temporal(), origin.temporal());

  obs.boost(v);
  auto t2 = obs.make_transform_from(*rootFrame);
  auto p2 = t2.inverse().translation();
  // Boost shouldn't change observer position
  BOOST_CHECK_EQUAL(p1, p2);

  obs.advance(second);
  auto t3 = obs.make_transform_from(*rootFrame);
  auto p3 = t3.inverse().translation();
  // Now spatial bit should *not* be the same
  BOOST_CHECK_NE(p2.spatial(), p3.spatial());
}

}}

