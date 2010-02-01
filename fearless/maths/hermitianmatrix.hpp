#ifndef FEARLESS_MATHS__HERMITIANMATRIX_HPP
#define FEARLESS_MATHS__HERMITIANMATRIX_HPP

#include <fearless/maths/complex.hpp>

namespace fearless { namespace maths {

template<typename T, std::uint32_t Dim>
class HermitianMatrix {
  public:
    static std::uint32_t const num_rows = Dim;
    static std::uint32_t const num_cols = Dim;
    typedef typename T::value_type value_type;

    /** Constructor for Dim==2 */
    HermitianMatrix(T m00, Complex<T> m01, T m11)
    {
      BOOST_MPL_ASSERT_RELATION(Dim,==,2);
      diagonal_[0] = m00;
      diagonal_[1] = m11;
      upper_triangle_[0] = m01;
    }

    HermitianMatrix conjugate(
        SpecialLinearMatrix<Complex<value_type>> const&
      ) const;

    T const& diagonal(std::uint32_t const i) const {
      assert(i < Dim);
      return diagonal_[i];
    }
    Complex<T> const& upper_triangle(
        std::uint32_t const r, std::uint32_t const c
      ) const {
      assert(r<c);
      std::uint32_t const i =
        upper_triangle_.size()-((Dim-r)*(Dim-r-1)/2)+c-r-1;
      assert(i < upper_triangle_.size());
      return upper_triangle_[i];
    }
  private:
    std::array<T, Dim> diagonal_;
    std::array<Complex<T>, Dim*(Dim-1)/2> upper_triangle_;
};

template<std::uint32_t Row, std::uint32_t Col, typename T, std::uint32_t Dim>
inline T const& matrix_element(
    HermitianMatrix<T, Dim> m,
    typename std::enable_if<Row==Col, int>::type = 0
  ) {
  BOOST_MPL_ASSERT_RELATION(Row,<,Dim);
  return m.diagonal(Row);
}

template<std::uint32_t Row, std::uint32_t Col, typename T, std::uint32_t Dim>
inline Complex<T> const& matrix_element(
    HermitianMatrix<T, Dim> m,
    typename std::enable_if<(Row<Col), int>::type = 0
  ) {
  BOOST_MPL_ASSERT_RELATION(Col,<,Dim);
  return m.upper_triangle(Row, Col);
}

template<std::uint32_t Row, std::uint32_t Col, typename T, std::uint32_t Dim>
inline Complex<T> matrix_element(
    HermitianMatrix<T, Dim> m,
    typename std::enable_if<(Row>Col), int>::type = 0
  ) {
  BOOST_MPL_ASSERT_RELATION(Row,<,Dim);
  return m.upper_triangle(Col, Row).conj();
}

template<typename T, std::uint32_t Dim>
HermitianMatrix<T, Dim> HermitianMatrix<T, Dim>::conjugate(
    SpecialLinearMatrix<Complex<value_type>> const& A
  ) const
{
  BOOST_STATIC_ASSERT(Dim == 2);

  // I am X = [ x  z ]
  //          [ z' y ]
  // where x,y are real, and ' is complex conjugation
  T const x = diagonal_[0];
  T const y = diagonal_[1];
  Complex<T> const z = upper_triangle_[0];

  // Conjugating X by A = [ a b ]
  //                      [ c d ]
  //
  typedef Complex<value_type> C;
  C const a = A.a();
  C const b = A.b();
  C const c = A.c();
  C const d = A.d();

  value_type const a_norm = a.norm_squared();
  value_type const b_norm = b.norm_squared();
  value_type const c_norm = c.norm_squared();
  value_type const d_norm = d.norm_squared();

  // Output is M, with
  // M_{0,0} = aa'x + bb'y + 2Re(ab'z)
  T const m00 = a_norm*x + b_norm*y + (a*b.conj()*z).real()*value_type(2);
  // M_{1,1} = cc'x + dd'y + 2Re(cd'z)
  T const m11 = c_norm*x + d_norm*y + (c*d.conj()*z).real()*value_type(2);
  // M_{0,1} = ac'x + bd'y + bc'z' + ad'z
  Complex<T> const m01 =
    a*c.conj()*x + b*d.conj()*y + b*c.conj()*z.conj() + a*d.conj()*z;

  return HermitianMatrix(m00, m01, m11);
}

}}

#endif // FEARLESS_MATHS__HERMITIANMATRIX_HPP

