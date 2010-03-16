#ifndef FEARLESS_MATHS__SIGN_HPP
#define FEARLESS_MATHS__SIGN_HPP

namespace fearless { namespace maths {

/** \brief Sign function
 *
 * \param x value to determine sign of
 *
 * \return 1, -1 or 0 according to the sign of x. */
template<typename T>
inline int sign(T const x) {
  if (x>0) {
    return 1;
  } else if (x<0) {
    return -1;
  } else {
    return 0;
  }
}

}}

#endif // FEARLESS_MATHS__SIGN_HPP

