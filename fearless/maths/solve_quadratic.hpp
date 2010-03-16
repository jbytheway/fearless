#ifndef FEARLESS_MATHS__SOLVE_QUADRATIC_HPP
#define FEARLESS_MATHS__SOLVE_QUADRATIC_HPP

#include <boost/tuple/tuple.hpp>

#include <fearless/maths/api.hpp>

namespace fearless { namespace maths {

FEARLESS_MATHS_API boost::tuple<double,double> solve_quadratic(
    const double a,
    const double b,
    const double c
  );

}}

#endif // FEARLESS_MATHS__SOLVE_QUADRATIC_HPP

