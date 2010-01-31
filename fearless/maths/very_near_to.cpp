#include <fearless/maths/very_near_to.hpp>

#include <cmath>

namespace fearless { namespace maths {

bool very_near_to(double const x, double const y, double const tolerance)
{
  return std::fabs(x-y)/(std::fabs(x)+std::fabs(y)) < tolerance;
}

}}

