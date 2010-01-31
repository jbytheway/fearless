#ifndef FEARLESS_MATHS__VERY_NEAR_TO_HPP
#define FEARLESS_MATHS__VERY_NEAR_TO_HPP

namespace fearless { namespace maths {

// Note that other implementations of very_near_to may be found by ADL, e.g.
// for ThreeVector; see corresponding headers

bool very_near_to(double const x, double const y, double const tolerance);

}}

#endif // FEARLESS_MATHS__VERY_NEAR_TO_HPP

