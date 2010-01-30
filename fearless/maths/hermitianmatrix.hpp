#ifndef FEARLESS_MATHS__HERMITIANMATRIX_HPP
#define FEARLESS_MATHS__HERMITIANMATRIX_HPP

namespace fearless { namespace maths {

template<typename T, std::uint32_t Dim>
class HermitianMatrix {
  public:
    typedef typename T::value_type value_type;

    /** Constructor for Dim==2 */
    HermitianMatrix(T m00, std::complex<T> m01, T m11)
    {
      BOOST_MPL_ASSERT_RELATION(Dim,==,2);
      diagonal_[0] = m00;
      diagonal_[1] = m11;
      upper_triangle_[0] = m01;
    }

    HermitianMatrix conjugate(
        SpecialLinearMatrix<std::complex<value_type>, Dim> const&
      ) const;

    T const& diagonal(std::uint32_t const i) const {
      assert(i < Dim);
      return diagonal_[i];
    }
    std::complex<T> const& upper_triangle(
        std::uint32_t const r, std::uint32_t const c
      ) const {
      assert(r<c);
      std::uint32_t const i = upper_triangle_.size()-((Dim-r)*(Dim-r-1)/2)+c;
      assert(i < upper_triangle_.size());
      return upper_triangle_[i];
    }
  private:
    std::array<T, Dim> diagonal_;
    std::array<std::complex<T>, Dim*(Dim-1)/2> upper_triangle_;
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
inline std::complex<T> const& matrix_element(
    HermitianMatrix<T, Dim> m,
    typename std::enable_if<(Row<Col), int>::type = 0
  ) {
  BOOST_MPL_ASSERT_RELATION(Col,<,Dim);
  return m.upper_triangle(Row, Col);
}

template<std::uint32_t Row, std::uint32_t Col, typename T, std::uint32_t Dim>
inline std::complex<T> matrix_element(
    HermitianMatrix<T, Dim> m,
    typename std::enable_if<(Row>Col), int>::type = 0
  ) {
  BOOST_MPL_ASSERT_RELATION(Row,<,Dim);
  return conj(m.upper_element(Col, Row));
}

}}

#endif // FEARLESS_MATHS__HERMITIANMATRIX_HPP

