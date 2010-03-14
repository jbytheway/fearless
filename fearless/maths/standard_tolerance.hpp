#ifndef FEARLESS_MATHS__STANDARD_TOLERANCE_HPP
#define FEARLESS_MATHS__STANDARD_TOLERANCE_HPP

namespace fearless { namespace maths {

/** \brief Tolerance used by default in very_near_to.
 *
 * 1e-8 is reasonable if floats were ever involved; 1e-15 is perhaps better for
 * doubles.
 */
static double const standard_tolerance = 1e-8;

}}

#endif // FEARLESS_MATHS__STANDARD_TOLERANCE_HPP

