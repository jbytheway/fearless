#ifndef FEARLESS_MATHS__DIVIDE_ROND_UP_HPP
#define FEARLESS_MATHS__DIVIDE_ROND_UP_HPP

#include <boost/type_traits/is_integral.hpp>
#include <boost/mpl/assert.hpp>

namespace fearless { namespace maths {

template<typename Integer1, typename Integer2>
inline Integer1 divide_round_up(Integer1 const n, Integer2 const d) {
  BOOST_MPL_ASSERT((boost::is_integral<Integer1>));
  BOOST_MPL_ASSERT((boost::is_integral<Integer2>));
  return (n+d-1)/d;
}

}}

#endif // FEARLESS_MATHS__DIVIDE_ROND_UP_HPP

