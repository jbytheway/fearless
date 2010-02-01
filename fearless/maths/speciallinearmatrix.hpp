#ifndef FEARLESS_MATHS__SPECIALLINEARMATRIX_HPP
#define FEARLESS_MATHS__SPECIALLINEARMATRIX_HPP

#include <array>

namespace fearless { namespace maths {

/** \brief A 2x2 matrix of determinant 1 */
template<typename T>
class SpecialLinearMatrix {
  public:
    static SpecialLinearMatrix scale_by(T const scale);

    SpecialLinearMatrix(T const& a, T const& b, T const& c, T const& d)
    {
      // Find the scale factor we'll need to make the determinant 1
      T const sqrt_det = sqrt(a*d - b*c);
      using std::isfinite;
      assert(isfinite(sqrt_det));
      assert(sqrt_det != 0.0);
      elem_[0][0] = a/sqrt_det;
      elem_[0][1] = b/sqrt_det;
      elem_[1][0] = c/sqrt_det;
      elem_[1][1] = d/sqrt_det;
    }

    T const& a() const { return elem_[0][0]; }
    T const& b() const { return elem_[0][1]; }
    T const& c() const { return elem_[1][0]; }
    T const& d() const { return elem_[1][1]; }

    SpecialLinearMatrix inverse() const;

    friend SpecialLinearMatrix
    operator*(SpecialLinearMatrix const& l, SpecialLinearMatrix const& r) {
      T const a = l.a() * r.a() + l.b() * r.c();
      T const b = l.a() * r.b() + l.b() * r.d();
      T const c = l.c() * r.a() + l.d() * r.c();
      T const d = l.c() * r.b() + l.d() * r.d();
      return SpecialLinearMatrix(a, b, c, d);
    }

    friend std::ostream&
    operator<<(std::ostream& o, SpecialLinearMatrix const& m) {
      o << '[' << m.elem_[0][0] << ", " << m.elem_[0][1] << "]\n";
      o << '[' << m.elem_[1][0] << ", " << m.elem_[1][1] << "]\n";
      return o;
    }
  private:
    std::array<std::array<T, 2>, 2> elem_;
};

/** \brief Creates a matrix which scales by the given amount in CP_1 */
template<typename T>
SpecialLinearMatrix<T> SpecialLinearMatrix<T>::scale_by(T const scale)
{
  T const sqrt_scale = sqrt(scale);
  return SpecialLinearMatrix(sqrt_scale, 0, 0, 1.0/sqrt_scale);
}

template<typename T>
SpecialLinearMatrix<T> SpecialLinearMatrix<T>::inverse() const
{
  return SpecialLinearMatrix(d(), -b(), -c(), a());
}

}}

#endif // FEARLESS_MATHS__SPECIALLINEARMATRIX_HPP 

