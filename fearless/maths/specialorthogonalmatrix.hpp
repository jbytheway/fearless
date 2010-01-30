#ifndef FEARLESS_MATHS__SPECIALORTHOGONALMATRIX_HPP
#define FEARLESS_MATHS__SPECIALORTHOGONALMATRIX_HPP

#include <boost/math/quaternion.hpp>

namespace fearless { namespace maths {

template<typename T>
class SpecialOrthogonalMatrix {
  public:
    SpecialOrthogonalMatrix<T> rotation_from_to();
  private:
    boost::math::quaternion<T> representation;
};

}}

#endif // FEARLESS_MATHS__SPECIALORTHOGONALMATRIX_HPP 

