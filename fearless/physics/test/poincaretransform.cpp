#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <fearless/physics/poincaretransform.hpp>

#include <fearless/physics/conventionalreality.hpp>

namespace fearless { namespace physics {

typedef ConventionalReality Reality;
typedef PoincareTransform<Reality, double> PT;
typedef Event<Reality, double> Ev;
using std::cout;
using std::endl;

BOOST_AUTO_TEST_CASE(translation_translates)
{
  Ev origin{};
  Ev second{1.0*units::second, Displacement<double>{}};

  PT time_translate(second);

  BOOST_CHECK_EQUAL(time_translate.apply(origin), second);
  BOOST_CHECK_EQUAL(time_translate.apply(second), 2.0*second);
}

BOOST_AUTO_TEST_CASE(transforms_compose)
{
  Ev origin{};
  Ev second{1.0*units::second, Displacement<double>{}};
  Velocity<double> v{1.0*units::metre_per_second, units::zero, units::zero};

  PT time_translate(second);
  PT boost(LorentzTransform<Reality, double>::boost(v));

  BOOST_CHECK_EQUAL(
      (boost * time_translate).translation(),
      (boost * time_translate).apply(origin)
    );

  // Check that composition acts properly on the origin
  BOOST_CHECK_EQUAL(
      boost.apply(time_translate.apply(origin)),
      (boost * time_translate).apply(origin)
    );
}

BOOST_AUTO_TEST_CASE(inverses_invert)
{
  Ev origin{};
  Ev second{1.0*units::second, Displacement<double>{}};
  Velocity<double> v{1.0*units::metre_per_second, units::zero, units::zero};

  PT time_translate(second);
  PT boost(LorentzTransform<Reality, double>::boost(v));
  PT product = boost*time_translate;

  BOOST_CHECK_EQUAL(origin, boost.inverse().apply(boost.apply(origin)));
  BOOST_CHECK_EQUAL(
      origin, time_translate.inverse().apply(time_translate.apply(origin))
    );
  BOOST_CHECK_EQUAL(origin, product.inverse().apply(product.apply(origin)));
}

}}

