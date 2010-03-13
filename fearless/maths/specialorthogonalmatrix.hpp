#ifndef FEARLESS_MATHS__SPECIALORTHOGONALMATRIX_HPP
#define FEARLESS_MATHS__SPECIALORTHOGONALMATRIX_HPP

#include <boost/math/quaternion.hpp>

#include <fearless/fatal.hpp>
#include <fearless/units/quantity.hpp>
#include <fearless/units/angle.hpp>
#include <fearless/maths/standard_tolerance.hpp>
#include <fearless/maths/very_near_to.hpp>
#include <fearless/maths/matrix3.hpp>

namespace fearless { namespace maths {

template<typename T>
class SpecialOrthogonalMatrix {
  public:
    typedef boost::math::quaternion<T> Representation;

    template<typename ThreeVector>
    static SpecialOrthogonalMatrix<T>
    rotation_from_to(ThreeVector const&, ThreeVector const&);

    template<int Axis, typename U>
    static SpecialOrthogonalMatrix
    axis_rotation(units::quantity<units::radian_angle, U> const&);

    template<typename U>
    static SpecialOrthogonalMatrix
    x_rotation(units::quantity<units::radian_angle, U> const&);

    template<typename U>
    static SpecialOrthogonalMatrix
    y_rotation(units::quantity<units::radian_angle, U> const&);

    template<typename U>
    static SpecialOrthogonalMatrix
    z_rotation(units::quantity<units::radian_angle, U> const&);

    Representation const& as_quaternion() const { return representation_; }

    SpecialOrthogonalMatrix inverse() const;

    Matrix3<T> to_matrix() const;
  private:
    SpecialOrthogonalMatrix(T const a, T const b, T const c, T const d);
    explicit SpecialOrthogonalMatrix(Representation r) : representation_(r) {}

    Representation representation_;
};

template<typename T>
template<typename ThreeVector>
SpecialOrthogonalMatrix<T> SpecialOrthogonalMatrix<T>::rotation_from_to(
    ThreeVector const& v0, ThreeVector const& v1
  )
{
  // Implementation adapted from Celestia
  // Original was
  // Copyright (C) 2000-2006, Chris Laurel <claurel@shatters.net>

  assert(v0.norm_squared() == 1);
  assert(v1.norm_squared() == 1);

  // We need sine and cosine of half the angle between v0 and v1, so
  // compute the vector halfway between v0 and v1. The cross product of
  // half and v1 gives the imaginary part of the quaternion
  // (axis * sin(angle/2)), and the dot product of half and v1 gives
  // the real part.
  auto half = v0 + v1;

  auto const hl = half.norm();
  if (hl > 0.0)
  {
    half /= hl; // normalize

    // The magnitude of rotAxis is the sine of half the angle between
    // v0 and v1.
    auto const rotAxis = cross_product(half, v1);
    auto const cosAngle = dot_product(half, v1);
    return SpecialOrthogonalMatrix(
        cosAngle, rotAxis.x(), rotAxis.y(), rotAxis.z()
      );
  }
  else
  {
    // The vectors point in exactly opposite directions, so there is
    // no unique axis of rotation.  We have to find an axis orthogonal to v0
    // and v1 and half-rotate around it
    if (v0.x() == 0) {
      // v0 in y-z plane, so rotate around x axis
      return SpecialOrthogonalMatrix(0.0, 1.0, 0.0, 0.0);
    } else {
      // We can pick this vector and it will be non-zero and orthogonal to v0
      ThreeVector axis{v0.y(), -v0.x(), 0.0};
      axis /= axis.norm();
      return SpecialOrthogonalMatrix(0.0, axis.x(), axis.y(), axis.z());
    }
  }
}

template<typename T>
template<int Axis, typename U>
SpecialOrthogonalMatrix<T>
SpecialOrthogonalMatrix<T>::axis_rotation(
    units::quantity<units::radian_angle, U> const& angle
  )
{
  BOOST_MPL_ASSERT_RELATION(Axis, >=, 0);
  BOOST_MPL_ASSERT_RELATION(Axis, <, 3);
  T const s = sin(angle * U(0.5));
  T const c = cos(angle * U(0.5));
  return SpecialOrthogonalMatrix(c, s*(Axis==0), s*(Axis==1), s*(Axis==2));
}

template<typename T>
template<typename U>
SpecialOrthogonalMatrix<T>
SpecialOrthogonalMatrix<T>::x_rotation(
    units::quantity<units::radian_angle, U> const& angle
  )
{
  return axis_rotation<0>(angle);
}

template<typename T>
template<typename U>
SpecialOrthogonalMatrix<T>
SpecialOrthogonalMatrix<T>::y_rotation(
    units::quantity<units::radian_angle, U> const& angle
  )
{
  return axis_rotation<1>(angle);
}

template<typename T>
template<typename U>
SpecialOrthogonalMatrix<T>
SpecialOrthogonalMatrix<T>::z_rotation(
    units::quantity<units::radian_angle, U> const& angle
  )
{
  return axis_rotation<2>(angle);
}

template<typename T>
SpecialOrthogonalMatrix<T> SpecialOrthogonalMatrix<T>::inverse() const
{
  return SpecialOrthogonalMatrix(conj(representation_));
}

template<typename T>
Matrix3<T> SpecialOrthogonalMatrix<T>::to_matrix() const
{
  T const w = as_quaternion().R_component_1();
  T const x = as_quaternion().R_component_2();
  T const y = as_quaternion().R_component_3();
  T const z = as_quaternion().R_component_4();
  T const wx = w * x * 2;
  T const wy = w * y * 2;
  T const wz = w * z * 2;
  T const xx = x * x * 2;
  T const xy = x * y * 2;
  T const xz = x * z * 2;
  T const yy = y * y * 2;
  T const yz = y * z * 2;
  T const zz = z * z * 2;

  return Matrix3<T>(
      (1 - yy - zz),     (xy - wz),     (xz + wy),
          (xy + wz), (1 - xx - zz),     (yz - wx),
          (xz - wy),     (yz + wx), (1 - xx - yy)
    );
}

template<typename T>
SpecialOrthogonalMatrix<T>::SpecialOrthogonalMatrix(
    T const a, T const b, T const c, T const d
  ) :
  representation_(a, b, c, d)
{
  if (!very_near_to(norm(representation_), 1.0, standard_tolerance)) {
    FEARLESS_FATAL(
        "[SpecialOrthogonalMatrix] determinant-1 == " <<
        norm(representation_)-1
      );
  }
}

template<typename T, typename ThreeVector>
inline typename std::enable_if<
  IsThreeVector<ThreeVector>::value, ThreeVector
>::type
operator*(SpecialOrthogonalMatrix<T> const& l, ThreeVector const& r)
{
  return l.to_matrix()*r;
}

}}

#endif // FEARLESS_MATHS__SPECIALORTHOGONALMATRIX_HPP 

