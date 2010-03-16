#ifndef FEARLESS_MATHS__SOLVE_QUADRATIC_HPP
#define FEARLESS_MATHS__SOLVE_QUADRATIC_HPP

#include <boost/tuple/tuple.hpp>

namespace fearless { namespace maths {

boost::tuple<double,double> solve_quadratic(
    const double a,
    const double b,
    const double c
  );

}}

#endif // FEARLESS_MATHS__SOLVE_QUADRATIC_HPP

