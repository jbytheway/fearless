#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <fearless/units/zero.hpp>
#include <fearless/units/time.hpp>
#include <fearless/units/length.hpp>
#include <fearless/maths/check_very_near.hpp>
#include <fearless/physics/conventionalreality.hpp>
#include <fearless/physics/lorentztransform.hpp>
#include <fearless/physics/displacement.hpp>

namespace fearless { namespace physics {

typedef ConventionalReality Reality;
typedef LorentzTransform<Reality, double> LT;
typedef Event<Reality, double> Ev;
using std::cout;
using std::endl;

BOOST_AUTO_TEST_CASE(rotation_transforms_sensibly)
{
  typedef physics::ThreeVector<units::quantity<units::dimensionless, double>>
    Vector;
  Vector const e0{1, 0, 0};
  Vector const e1{0, 1, 0};
  Vector const e2{0, 0, 1};
  Ev ev0(0.0*units::seconds, e0*units::metre);
  Ev ev1(0.0*units::seconds, e1*units::metre);
  Ev ev2(0.0*units::seconds, e2*units::metre);
  typedef maths::SpecialOrthogonalMatrix<double> Matrix;
  {
    Matrix m = Matrix::rotation_from_to(e0, e0);
    auto transform = LT::rotation(m);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev0), ev0);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev1), ev1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev2), ev2);
  }
  {
    Matrix m = Matrix::rotation_from_to(e1, e1);
    auto transform = LT::rotation(m);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev0), ev0);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev1), ev1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev2), ev2);
  }
  {
    Matrix m = Matrix::rotation_from_to(e2, e2);
    auto transform = LT::rotation(m);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev0), ev0);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev1), ev1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev2), ev2);
  }
  {
    Matrix m = Matrix::rotation_from_to(e0, e1);
    auto transform = LT::rotation(m);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev0), ev1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev1), -ev0);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev2), ev2);
  }
  {
    Matrix m = Matrix::rotation_from_to(e0, e2);
    auto transform = LT::rotation(m);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev0), ev2);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev1), ev1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev2), -ev0);
  }
  {
    Matrix m = Matrix::rotation_from_to(e1, e2);
    auto transform = LT::rotation(m);
    /*cout << "m = " << m.as_quaternion() << endl;
    cout << "transform:\n"; transform.dump(std::cout); cout << endl;*/
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev0), ev0);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev1), ev2);
    FEARLESS_MATHS_CHECK_VERY_NEAR(transform.apply(ev2, true), -ev1);
  }
}

BOOST_AUTO_TEST_CASE(boost_transforms_sensibly_along_path)
{
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

