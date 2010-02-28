#ifndef FEARLESS_MATHS__ROUND_UP_TO_MULTIPLE_HPP
#define FEARLESS_MATHS__ROUND_UP_TO_MULTIPLE_HPP

#include <fearless/maths/divide_round_up.hpp>

namespace fearless { namespace maths {

template<typename Integer1, typename Integer2>
inline Integer1 round_up_to_multiple(Integer1 const n, Integer2 const d) {
  BOOST_MPL_ASSERT((boost::is_integral<Integer1>));
  BOOST_MPL_ASSERT((boost::is_integral<Integer2>));
  return divide_round_up(n,d)*d;
}

}}

#endif // FEARLESS_MATHS__ROUND_UP_TO_MULTIPLE_HPP

