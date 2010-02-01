#ifndef FEARLESS_MATHS__VERY_NEAR_TO_HPP
#define FEARLESS_MATHS__VERY_NEAR_TO_HPP

#include <boost/units/quantity.hpp>

namespace fearless { namespace maths {

// Note that other implementations of very_near_to may be found by ADL, e.g.
// for ThreeVector; see corresponding headers

bool very_near_to(double const x, double const y, double const tolerance);

template<typename Unit, typename T>
inline bool very_near_to(
    boost::units::quantity<Unit, T> const& x,
    boost::units::quantity<Unit, T> const& y,
    double const tolerance
  ) {
  return very_near_to(x.value(), y.value(), tolerance);
}

}}

#endif // FEARLESS_MATHS__VERY_NEAR_TO_HPP

