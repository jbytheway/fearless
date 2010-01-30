#ifndef FEARLESS_MATHS__SPECIALLINEARMATRIX_HPP
#define FEARLESS_MATHS__SPECIALLINEARMATRIX_HPP

#include <array>

namespace fearless { namespace maths {

template<typename T, std::uint32_t Dim>
class SpecialLinearMatrix {
  public:
  private:
    std::array<std::array<T, Dim>, Dim> elem_;
};

}}

#endif // FEARLESS_MATHS__SPECIALLINEARMATRIX_HPP 

