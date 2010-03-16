#ifndef FEARLESS_PHYSICS__LUMINOSITYCLASS_HPP
#define FEARLESS_PHYSICS__LUMINOSITYCLASS_HPP

#include <ostream>
#include <type_traits>

#include <boost/preprocessor/seq/enum.hpp>

#include <fearless/physics/api.hpp>

namespace fearless { namespace physics {

#define FEARLESS_PHYSICS_LUMINOSITYCLASS_VALUES() \
  (Ia0) \
  (Ia) \
  (Ib) \
  (II) \
  (III) \
  (IV) \
  (V) \
  (VI) \
  (Unknown) \
  (Max)

enum class LuminosityClass {
  BOOST_PP_SEQ_ENUM(FEARLESS_PHYSICS_LUMINOSITYCLASS_VALUES())
};

FEARLESS_PHYSICS_API std::ostream&
operator<<(std::ostream&, LuminosityClass const);

inline bool operator<(LuminosityClass const l, LuminosityClass const r) {
  typedef std::make_unsigned<LuminosityClass>::type Integer;
  return Integer(l) < Integer(r);
}

}}

#endif // FEARLESS_PHYSICS__LUMINOSITYCLASS_HPP

