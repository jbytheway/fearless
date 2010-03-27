#ifndef FEARLESS_MATHS__CLAMP_HPP
#define FEARLESS_MATHS__CLAMP_HPP

#include <algorithm>

namespace fearless { namespace maths {

template<typename T>
T clamp(T const& val, T const& min, T const& max)
{
  return std::min(std::max(val, min), max);
}

}}

#endif // FEARLESS_MATHS__CLAMP_HPP

