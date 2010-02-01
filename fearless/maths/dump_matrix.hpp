#ifndef FEARLESS_MATHS__DUMP_MATRIX_HPP
#define FEARLESS_MATHS__DUMP_MATRIX_HPP

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

namespace fearless { namespace maths {

namespace dump_matrix_detail {

template<typename Matrix, typename Row>
struct DumpEntry {
  DumpEntry(std::ostream& o, Matrix const& m) : o_(o), m_(m) {}

  template<typename Col>
  void operator()(Col col) const {
    std::uint32_t const cols = Matrix::num_cols;
    if (col == 0) o_ << "[ ";
    o_ << matrix_element<Row::value, Col::value>(m_);
    if (col == cols-1) o_ << " ]\n"; else o_ << ", ";
  }

  std::ostream& o_;
  Matrix const& m_;
};

template<typename Matrix>
struct DumpRow {
  DumpRow(std::ostream& o, Matrix const& m) : o_(o), m_(m) {}

  template<typename Row>
  void operator()(Row) const {
    std::uint32_t const cols = Matrix::num_cols;
    boost::mpl::for_each<boost::mpl::range_c<std::uint32_t, 0, cols>>(
        dump_matrix_detail::DumpEntry<Matrix, Row>(o_, m_)
      );
  }

  std::ostream& o_;
  Matrix const& m_;
};

}

template<typename Matrix>
void dump_matrix(std::ostream& o, Matrix const& m)
{
  std::uint32_t const rows = Matrix::num_rows;

  boost::mpl::for_each<boost::mpl::range_c<std::uint32_t, 0, rows>>(
      dump_matrix_detail::DumpRow<Matrix>(o, m)
    );
}

}}

#endif // FEARLESS_MATHS__DUMP_MATRIX_HPP

