#ifndef FEARLESS_MATHS__CHECK_VERY_NEAR_HPP
#define FEARLESS_MATHS__CHECK_VERY_NEAR_HPP

#include <boost/test/test_tools.hpp>

#include <fearless/maths/very_near_to.hpp>
#include <fearless/maths/standard_tolerance.hpp>

#define FEARLESS_MATHS_CHECK_VERY_NEAR(x, y)                         \
  do {                                                               \
    using fearless::maths::very_near_to;                             \
    BOOST_CHECK_MESSAGE(                                             \
        very_near_to((x), (y), fearless::maths::standard_tolerance), \
        (x) << " is not very near to " << (y)                        \
      );                                                             \
  } while (false)

#endif // FEARLESS_MATHS__CHECK_VERY_NEAR_HPP

