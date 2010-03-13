#ifndef FEARLESS_MATHS__MATRIX_HPP
#define FEARLESS_MATHS__MATRIX_HPP

#include <array>

#include <boost/foreach.hpp>

#include <fearless/maths/isthreevector.hpp>

namespace fearless { namespace maths {

template<typename T>
class Matrix3 {
  public:
    Matrix3(
        T a00, T a01, T a02,
        T a10, T a11, T a12,
        T a20, T a21, T a22
      )
    {
      /** \bug Should use initializer here but gcc doesn't support it */
      Elements elements = {
        {{{a00, a01, a02}}, {{a10, a11, a12}}, {{a20, a21, a22}}}
      };
      elements_ = elements;
    }

    T operator()(size_t const r, size_t const c) const {
      assert(r < 3);
      assert(c < 3);
      return elements_[r][c];
    }

    Matrix3& operator*=(double const r) {
      BOOST_FOREACH(Row& c, elements_) {
        BOOST_FOREACH(T& e, c) {
          e *= r;
        }
      }
      return *this;
    }
  private:
    typedef std::array<T, 3> Row;
    typedef std::array<Row, 3> Elements;
    Elements elements_;
};

template<typename T>
inline Matrix3<T>
operator*(double const l, Matrix3<T> const& r)
{
  Matrix3<T> result(r);
  return result *= l;
}

template<typename T, typename ThreeVector>
inline typename std::enable_if<
  IsThreeVector<ThreeVector>::value, ThreeVector
>::type
operator*(Matrix3<T> const& l, ThreeVector const& r)
{
  return ThreeVector(
      l(0, 0)*r.x() + l(0, 1)*r.y() + l(0, 2)*r.z(),
      l(1, 0)*r.x() + l(1, 1)*r.y() + l(1, 2)*r.z(),
      l(2, 0)*r.x() + l(2, 1)*r.y() + l(2, 2)*r.z()
    );
}

template<typename T, typename ThreeVector>
inline typename std::enable_if<
  IsThreeVector<ThreeVector>::value, ThreeVector
>::type
operator*(ThreeVector const& l, Matrix3<T> const& r)
{
  return ThreeVector(
      r(0, 0)*l.x() + r(1, 0)*l.y() + r(2, 0)*l.z(),
      r(0, 1)*l.x() + r(1, 1)*l.y() + r(2, 1)*l.z(),
      r(0, 2)*l.x() + r(1, 2)*l.y() + r(2, 2)*l.z()
    );
}

}}

#endif // FEARLESS_MATHS__MATRIX_HPP

