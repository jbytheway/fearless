#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <fearless/maths/specialorthogonalmatrix.hpp>
#include <fearless/maths/check_very_near.hpp>

#include <fearless/units/dimensionless.hpp>
#include <fearless/physics/threevector.hpp>

namespace fearless { namespace maths {

BOOST_AUTO_TEST_CASE(rotation_from_to_rotates)
{
  typedef physics::ThreeVector<units::quantity<units::dimensionless, double>>
    Vector;
  Vector const e0{1, 0, 0};
  Vector const e1{0, 1, 0};
  Vector const e2{0, 0, 1};
  typedef SpecialOrthogonalMatrix<double> Matrix;
  {
    Matrix m = Matrix::rotation_from_to(e0, e0);
    FEARLESS_MATHS_CHECK_VERY_NEAR(m*e0, e0);
  }
  {
    Matrix m = Matrix::rotation_from_to(e0, e1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(m*e0, e1);
  }
  {
    Matrix m = Matrix::rotation_from_to(e0, e2);
    FEARLESS_MATHS_CHECK_VERY_NEAR(m*e0, e2);
  }
  {
    Matrix m = Matrix::rotation_from_to(e0, -e0);
    FEARLESS_MATHS_CHECK_VERY_NEAR(m*e0, -e0);
  }
  {
    Matrix m = Matrix::rotation_from_to(e1, -e1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(m*e1, -e1);
  }
  {
    Matrix m = Matrix::rotation_from_to(e1, -e1);
    FEARLESS_MATHS_CHECK_VERY_NEAR(m*e1, -e1);
  }
}

}}

